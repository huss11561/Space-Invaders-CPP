#include "bullet.h"

// Konstruktor für die Klasse Bullet, initialisiert die Position (startX, startY)
// und ob die Kugel vom Spieler (isPlayer) stammt
Bullet::Bullet(int startX, int startY, bool isPlayer)
    : x(startX), y(startY), fromPlayer(isPlayer) {}

// Getter-Funktion, um die x-Koordinate der Kugel zu erhalten
int Bullet::getX() const { return x; }

// Getter-Funktion, um die y-Koordinate der Kugel zu erhalten
int Bullet::getY() const { return y; }

// Methode, um die Kugel zu bewegen
void Bullet::move() {
    // Wenn die Kugel vom Spieler stammt, bewegt sie sich nach oben
    if (fromPlayer) {
        y -= 1; // Kugel bewegt sich nach oben
    } else { 
        // Wenn die Kugel nicht vom Spieler stammt, bewegt sie sich nach unten
        y += 1; // Kugel bewegt sich nach unten
    }
}

// Funktion, um zu überprüfen, ob die Kugel außerhalb des Bildschirms ist
// Gibt true zurück, wenn die Kugel außerhalb der Bildschirmhöhe ist, sonst false
bool Bullet::isOffScreen(int height) const {
    return y < 0 || y > height;
}

// Funktion, um zu überprüfen, ob die Kugel vom Spieler stammt
// Gibt true zurück, wenn die Kugel vom Spieler stammt, sonst false
bool Bullet::isFromPlayer() const {
    return fromPlayer;
}
