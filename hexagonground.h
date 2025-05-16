#include <QGraphicsPolygonItem>
#include <QPainter>

class HexagonItem : public QGraphicsPolygonItem {
public:
    HexagonItem(qreal size, QGraphicsItem *parent = nullptr)
        : QGraphicsPolygonItem(parent) {
        QPolygonF hexagon;
        for (int i = 0; i < 6; ++i) {
            qreal angle = 2 * M_PI * i / 6;  // 60 degrees per step
            hexagon << QPointF(size * cos(angle), size * sin(angle));
        }
        setPolygon(hexagon);

        // Style the hexagon
        setBrush(QColor(200, 200, 255));  // Light blue
        setPen(QPen(Qt::black, 2));

    }
};
