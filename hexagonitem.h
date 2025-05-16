#ifndef HEXAGONITEM_H
#define HEXAGONITEM_H

#include <QGraphicsPolygonItem>
#include <QObject>

class HexagonItem : public QGraphicsPolygonItem
{
    Q_OBJECT  // Important for signals/slots
public:
    explicit HexagonItem(QPolygonF polygon, QGraphicsItem *parent = nullptr);

signals:
    void hexagonClicked(QPointF scenePos);  // New signal

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // HEXAGONITEM_H
