//
// Created by oreste on 18/12/24.
//

#ifndef VORONOIDISCRETFB_MAINWINDOW_H
#define VORONOIDISCRETFB_MAINWINDOW_H


#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <vector>
#include <cmath>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void refreshPoints();  // Régénérer les points
    void changeDistanceType(int index);  // Changer la formule de distance

private:
    struct Point {
        int x, y;
        QColor color;
    };

    std::vector<Point> points;  // Ensemble de points
    int width = 500, height = 500;  // Taille de l'image
    int distanceType = 0;  // 0: Euclidienne, 1: Manhattan, 2: Chebyshev

    QPushButton *refreshButton;  // Bouton Refresh
    QComboBox *distanceSelector;  // Liste déroulante pour sélectionner la formule de distance

    double euclideanDistance(int x1, int y1, int x2, int y2);
    int manhattanDistance(int x1, int y1, int x2, int y2);
    int chebyshevDistance(int x1, int y1, int x2, int y2);
    void init();
};




#endif //VORONOIDISCRETFB_MAINWINDOW_H
