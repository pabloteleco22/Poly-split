#include "renderarea.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>

#include <cstdio>
#include <cfloat>

#include <../src/poly/polygon.hpp>

std::vector<Polygon> polygons;
std::vector<QColor> polygons_colors;

double squareToCut;
int selectedPolygon;

int showInfo = 0;
int showHelp = 1;

double scale = 1;
double offset_x = 0;
double offset_y = 0;

int mouseLeftPress = 0;
int mouse_x = 0;
int mouse_y = 0;
Point mouse;

double pointSize = 5;

int selectedPoint = -1;


void drawPoly(QPainter &painter, const Polygon &poly)
{
    QPolygonF polypon;
    for(unsigned i = 0; i < poly.size(); i++)
    {
        polypon << QPointF(poly[i].x, poly[i].y);
    }

    painter.drawPolygon(polypon);
}


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);

    //setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setPalette(pal);
    setMouseTracking(true);

    polygons_colors.push_back(Qt::darkRed);
    polygons_colors.push_back(Qt::green);
    polygons_colors.push_back(Qt::darkGreen);
    polygons_colors.push_back(Qt::blue);
    polygons_colors.push_back(Qt::darkBlue);
    polygons_colors.push_back(Qt::cyan);
    polygons_colors.push_back(Qt::darkCyan);
    polygons_colors.push_back(Qt::magenta);
    polygons_colors.push_back(Qt::darkMagenta);
    polygons_colors.push_back(Qt::darkYellow);
    polygons_colors.push_back(Qt::gray);
    polygons_colors.push_back(Qt::darkGray);

    initPolygons();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(Qt::black);

    if(showHelp)
    {
        int y = 0, dy = painter.fontMetrics().height() + 1.0;
        painter.drawText(10, y += dy, "Cut area square: " + QString::number(squareToCut));
        painter.drawText(10, y += dy, "Q/W - increase/decrease cut area square to 100");
        painter.drawText(10, y += dy, "q/w - increase/decrease cut area square to 10");
        painter.drawText(10, y += dy, "a/s - swith between areas");
        painter.drawText(10, y += dy, "r - to restore initial polygon");
        painter.drawText(10, y += dy, "i - show/hide polygons square value");
        painter.drawText(10, y += dy, "c - to cut area as black cut line shows");
        painter.drawText(10, y += dy, "h - show/hide this text");
        painter.drawText(10, y += dy, "Mouse wheel to adjust scale");
        painter.drawText(10, y += dy, "Left mouse click and drag'n'drop on background to move all scene");
        painter.drawText(10, y += dy, "Left mouse click and drag'n'drop on vertex to move vertices");
        painter.drawText(10, y += dy, "Right mouse click to select nearest polygon");
        painter.drawText(10, y += dy, "Middle mouse click to split edge of selected polygon");
    }

    painter.save();
    painter.translate(offset_x, offset_y);
    painter.scale(scale, scale);

    painter.setRenderHint(QPainter::Antialiasing, true);

    for(size_t i = 0; i < polygons.size(); i++)
    {
        painter.setPen(QPen(polygons_colors[i % polygons_colors.size()], 1));
        QColor c = QColor(polygons_colors[i % polygons_colors.size()]);
        c.setAlpha(40);
        painter.setBrush(c);
        drawPoly(painter, polygons[i]);

        if(showInfo)
        {
            Vector p = polygons[i].find_center();
            painter.drawText(QPointF(p.x, p.y), QString::number(polygons[i].count_square()));
        }
    }

    Polygon poly1, poly2;
    Segment cut;
    try {
        polygons[selectedPolygon].split(squareToCut, poly1, poly2, cut);
        painter.setPen(QPen(Qt::black, 1.5));
        //painter.setPen(QPen(Qt::white, 1.5));
        painter.drawLine(QPointF(cut.get_start().x, cut.get_start().y), QPointF(cut.get_end().x, cut.get_end().y));
    } catch (const Polygon::CannotSplitException &) {

    }

    if(showInfo)
    {
        painter.setPen(QPen(QColor(0, 0, 0, 50), 1));
        Vector np = polygons[selectedPolygon].find_nearest_point(mouse);
        painter.drawLine(QPointF(mouse.x, mouse.y), QPointF(np.x, np.y));
    }

    painter.setPen(QPen(QColor(250, 0, 0, 100), 3));
    painter.setBrush(Qt::transparent);
    drawPoly(painter, polygons[selectedPolygon]);
    for(size_t i = 0; i < polygons[selectedPolygon].size(); i++)
    {
        Vector p = polygons[selectedPolygon][i];
        painter.drawEllipse(QPointF(p.x, p.y), pointSize, pointSize);
    }

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        squareToCut += event->modifiers() == Qt::SHIFT ? 100 : 10;
        repaint();
    }
    if(event->key() == Qt::Key_W)
    {
        double t = squareToCut - (event->modifiers() == Qt::SHIFT ? 100 : 10);
        squareToCut = t < 10 ? 10 : t;
        repaint();
    }
    if(event->key() == Qt::Key_C)
    {
        Polygon poly1, poly2;
        Segment cut;
        try{
            polygons[selectedPolygon].split(squareToCut, poly1, poly2, cut);

            polygons[selectedPolygon] = poly1;
            polygons.push_back(poly2);

            if(poly1.count_square() < poly2.count_square())
            {
                selectedPolygon = polygons.size() - 1;
            }

            repaint();
        } catch (const Polygon::CannotSplitException &) {

        }
    }
    if(event->key() == Qt::Key_P)
    {
        for(size_t i = 0; i < polygons[selectedPolygon].size(); i++)
        {
            Vector p = polygons[selectedPolygon][i];
            fprintf(stdout, "polygons[0].push_back(Vector(%.*e, %.*e));\n", 50, p.x, 50, p.y);
        }
        fflush(stdout);
    }
    if(event->key() == Qt::Key_A)
    {
        if(selectedPolygon > 0)
        {
            selectedPolygon--;
        }
        repaint();
    }
    if(event->key() == Qt::Key_S)
    {
        if(selectedPolygon < (int)polygons.size() - 1)
        {
            selectedPolygon++;
        }
        repaint();
    }
    if(event->key() == Qt::Key_R)
    {
        initPolygons();
        repaint();
    }
    if(event->key() == Qt::Key_I)
    {
        showInfo = !showInfo;
        repaint();
    }
    if(event->key() == Qt::Key_H)
    {
        showHelp = !showHelp;
        repaint();
    }
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();

    mouse = Point((event->x() - offset_x) / scale, (event->y() - offset_y) / scale);

    if(event->button() == Qt::LeftButton)
    {
        for(size_t i = 0; i < polygons[selectedPolygon].size(); i++)
        {
            Point p = polygons[selectedPolygon][i];
            if(mouse.distance(p) < pointSize)
            {
                selectedPoint = i;
            }
        }

        mouseLeftPress = 1;
    }
    if(event->button() == Qt::MiddleButton)
    {
        polygons[selectedPolygon].split_nearest_edge(mouse);
    }
    if(event->button() == Qt::RightButton)
    {
        double minDist = DBL_MAX;
        for(size_t i = 0; i < polygons.size(); i++)
        {
            double dist = polygons[i].find_distance(mouse);
            if(dist < minDist)
            {
                minDist = dist;
                selectedPolygon = i;
            }
        }
        squareToCut = polygons[selectedPolygon].count_square() / 2.0;
        repaint();
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseLeftPress && selectedPoint != -1)
    {
        polygons[selectedPolygon][selectedPoint].x = polygons[selectedPolygon][selectedPoint].x + (event->x() - mouse_x) / scale;
        polygons[selectedPolygon][selectedPoint].y = polygons[selectedPolygon][selectedPoint].y + (event->y() - mouse_y) / scale;
    }
    else if(mouseLeftPress)
    {
        offset_x = offset_x + (event->x() - mouse_x);
        offset_y = offset_y + (event->y() - mouse_y);
    }

    mouse_x = event->x();
    mouse_y = event->y();
    mouse = Point((event->x() - offset_x) / scale, (event->y() - offset_y) / scale);
    repaint();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseLeftPress = 0;
        selectedPoint = -1;
    }
}

void RenderArea::wheelEvent(QWheelEvent *event)
{
    scale += 5 * scale / event->angleDelta().y();
    repaint();
}

void RenderArea::initPolygons()
{
    polygons.clear();
    polygons.push_back(Polygon());

    polygons[0].push_back(Point(450.0, 100.0));
    polygons[0].push_back(Point(900.0, 100.0));
    polygons[0].push_back(Point(900.0, 400.0));
    polygons[0].push_back(Point(450.0, 400.0));

    squareToCut = polygons[0].count_square() / 47.0;
    selectedPolygon = 0;
}
