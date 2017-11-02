#include "myitem.h"

MyItem::MyItem()
{
    //random start rotation
    angle = (qrand() % 360);
    setRotation(angle);

    //set the speed
    speed = 5;

    //random start position
    int StartX = 0;
    int StartY = 0;

    if((qrand() % 1))
    {
        StartX = (qrand() % 200);
        StartY = (qrand() % 200);
    }
    else
    {
        StartX = (qrand() % -100);
        StartY = (qrand() % -100);
    }

    setPos(mapToParent(StartX,StartY));
}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,20,20);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush Brush(Qt::gray);

    //basic Collision detection

    if(scene()->collidingItems(this).isEmpty())
    {
        //no collision
        Brush.setColor(Qt::green);
    }
    else
    {
        //collision!!!!
        Brush.setColor(Qt::red);

        //Set the position
        DoCollision();
    }

    painter->fillRect(rec,Brush);
    painter->drawRect(rec);

}

void MyItem::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();

    setPos(mapToParent(0,-(speed)));
}

void MyItem::DoCollision()
{
    //Get a new position

    //Change the angle with a little randomness
    if(((qrand() %1)))
    {
        setRotation(rotation() + (180 + (qrand() % 10)));
    }
    else
    {
        setRotation(rotation() + (180 + (qrand() % -10)));
    }

    //see if the new position is in bounds
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

    if(!scene()->sceneRect().contains((newpoint)))
    {
        //move it back in bounds
        newpoint = mapToParent(0,0);
    }
    else
    {
        //set the new position
        setPos(newpoint);
    }

}
