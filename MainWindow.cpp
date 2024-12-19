#include "MainWindow.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QPushButton>
#include <QComboBox>

// Constructeur de la fenêtre principale
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    // Initialisation des points aléatoires
    init();

    // Création du bouton Refresh
    refreshButton = new QPushButton("Refresh", this);
    refreshButton->setGeometry(width - 200, 10, 90, 30);  // Position du bouton
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshPoints);

    // Création de la liste déroulante pour choisir la distance
    distanceSelector = new QComboBox(this);
    distanceSelector->setGeometry(width - 100, 10, 90, 30);  // Position de la liste déroulante
    distanceSelector->addItem("Euclidienne");  // Option 0
    distanceSelector->addItem("Manhattan");    // Option 1
    distanceSelector->addItem("Chebyshev");    // Option 2
    connect(distanceSelector, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::changeDistanceType);
}

// Méthode paintEvent : Dessine le diagramme de Voronoï
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  // Objet QPainter pour dessiner

    // Parcourir chaque pixel de l'image (NxM)
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int minIndex = 0;  // Indice du point le plus proche
            double minDistance = euclideanDistance(x, y, points[0].x, points[0].y);  // Distance minimale initiale

            // Comparer la distance entre le pixel (x, y) et tous les points
            for (size_t i = 1; i < points.size(); ++i) {
                double dist;

                // Sélectionner la formule de distance en fonction de distanceType
                switch (distanceType) {
                    case 0: dist = euclideanDistance(x, y, points[i].x, points[i].y); break;  // Distance Euclidienne
                    case 1: dist = manhattanDistance(x, y, points[i].x, points[i].y); break;  // Distance Manhattan
                    case 2: dist = chebyshevDistance(x, y, points[i].x, points[i].y); break;  // Distance Chebyshev
                }

                // Mettre à jour l'indice et la distance minimale si nécessaire
                if (dist < minDistance) {
                    minDistance = dist;
                    minIndex = i;
                }
            }

            // Colorier le pixel avec la couleur du point le plus proche
            painter.setPen(points[minIndex].color);
            painter.drawPoint(x, y);
        }
    }
}

// Distance Euclidienne entre deux points (x1, y1) et (x2, y2)
double MainWindow::euclideanDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Distance de Manhattan entre deux points (x1, y1) et (x2, y2)
int MainWindow::manhattanDistance(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

// Distance de Chebyshev entre deux points (x1, y1) et (x2, y2)
int MainWindow::chebyshevDistance(int x1, int y1, int x2, int y2) {
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

// Méthode init : Initialise les points aléatoires pour le diagramme de Voronoï
void MainWindow::init() {
    points.clear();  // Vider la liste des points existants
    for (int i = 0; i < 10; ++i) {
        // Générer des points aléatoires avec des couleurs uniques
        points.push_back({QRandomGenerator::global()->bounded(width),   // Coordonnée x
                          QRandomGenerator::global()->bounded(height),  // Coordonnée y
                          QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 255)});  // Couleur
    }
}

// Slot refreshPoints : Régénère les points et rafraîchit l'affichage
void MainWindow::refreshPoints() {
    init();    // Réinitialiser les points aléatoires
    update();  // Redessiner la fenêtre avec les nouveaux points
}

// Slot changeDistanceType : Change la formule de distance sélectionnée
void MainWindow::changeDistanceType(int index) {
    distanceType = index;  // Mettre à jour le type de distance
    update();  // Redessiner la fenêtre avec la nouvelle formule
}
