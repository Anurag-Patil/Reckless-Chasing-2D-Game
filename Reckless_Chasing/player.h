#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QList>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>
#include <QPointF>
#include <iostream>
#include <QPoint>
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <math.h>
#include <QWidget>
#include <QGraphicsPixmapItem>
/**
 * @brief The Player class It is the object class that is used to create players on the screen
 */
class Player : public QGraphicsPixmapItem {
public :
    qreal radius = 50;
    QPointF initial_pos = QPointF(400,250);

    Player();
    ~Player();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setSpeed(int);
    int getSpeed();

protected:

public:
    qreal new_x, new_y;

private:
    int speed = 5;
    QPointF window_size = QPointF(1050,700);
    QSet<int> pressedKeys;
    void fixed_Pos(QPointF center, bool isUp);
    QPointF get_MousePos();
    bool is_boundary_crossed(double x, double y,double initialx, double initialy);
    QPointF window_origin, origin, mouse_pos, center;
    QGraphicsView *view;
};

#endif // PLAYER_H
