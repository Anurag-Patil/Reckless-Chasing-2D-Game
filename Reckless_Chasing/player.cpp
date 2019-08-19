#include "player.h"

Player::Player() {}

Player::~Player() {}

void Player::keyPressEvent(QKeyEvent *event) {
    pressedKeys.insert(reinterpret_cast<QKeyEvent*>(event)->key());

    if((pressedKeys.contains(Qt::Key_W))&&(pressedKeys.contains(Qt::Key_S))){
        //Do  nothing
    }
    else if(pressedKeys.contains(Qt::Key_W)) {
        QPointF center = get_MousePos();
        fixed_Pos(center,true);
    }
    else if(pressedKeys.contains(Qt::Key_S)) {
        QPointF center = get_MousePos();
        fixed_Pos(center,false);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    pressedKeys.remove(reinterpret_cast<QKeyEvent*>(event)->key());
}

void Player::setSpeed(const int newSpeed) {
    if (newSpeed >= 0) {
        this->speed = newSpeed;
    }
}

int Player::getSpeed() { return this->speed; }

/**
 * @brief Player::fixed_Pos It is used to update the position of the players based on the input
 */
void Player::fixed_Pos(QPointF center, bool isUp) {
    qreal dy = (center.y() - this->new_y);
    qreal dx = (center.x() - this->new_x);
    dy = (dy / sqrt(pow(dy,2) + pow(dx,2)));
    dx = (dx / sqrt(pow(dy,2) + pow(dx,2)));
    qreal x = 0,y = 0;

    if (isUp) {
        x = this->new_x + (this->speed * dx);
        y = this->new_y + (this->speed * dy);
    }
    else {
        x = this->new_x - (this->speed * dx);
        y = this->new_y - (this->speed * dy);
    }

    if (!is_boundary_crossed(x,y,this->initial_pos.x(),this->initial_pos.y())) {
        if (!(((center.x() - this->new_x)*(center.x() - (this->new_x + (this->speed * dx)))) < 0)) {
            this->new_x = x;
        }
        /*else {
            this->new_x = center.x() + 1;
        }*/
        if (!(((center.y() - this->new_y)*(center.y() - (this->new_y + (this->speed * dy)))) < 0)) {
            this->new_y = y;
        }
        /*else {
            this->new_y = center.y() + 1;
        }*/
    }
    else {
        if (x < -(this->initial_pos.x())) {
            this->new_x = (-(this->initial_pos.x()));
        }
        if (x > (window_size.x() - this->initial_pos.x() - (2 * this->radius))) {
            this->new_x = (window_size.x() - this->initial_pos.x() - (2 * this->radius));
        }
        if (y > (window_size.y() - this->initial_pos.y() - (2 * this->radius))) {
            this->new_y = (window_size.y() - this->initial_pos.y() - (2 * this->radius));
        }
        if (y < -(this->initial_pos.y())) {
            this->new_y = (-(this->initial_pos.y()));
        }
    }
}

/**
 * @brief Player::get_MousePos It is used to determine the position of the mouse
 */
QPointF Player::get_MousePos() {
    this->window_origin = QPointF(this->initial_pos.x(),this->initial_pos.y());
    this->view = this->scene()->views().first();
    this->origin = view->mapToGlobal(QPoint(0,0));
    this->mouse_pos = QCursor::pos();
    mouse_pos -= origin;
    mouse_pos -= window_origin;
    this->center = mouse_pos - QPointF(this->radius,this->radius);

    return center;
}

/**
 * @brief Player::is_boundary_crossed Is function is used to ensure that the players do not go outside the screen
 * @param x The current x-coordinate of the player
 * @param y The current y-coordinate of the player
 * @param initialx The previous x-coordinate of the player
 * @param initialy The previous y-coordinate of the player
 */
bool Player::is_boundary_crossed(double x, double y,double initialx, double initialy) {
    return ((x < -initialx) || (x > (window_size.x() - initialx - (2 * this->radius))) || (y > (window_size.y() - initialy - (2 * this->radius))) || (y < -initialy));
}
