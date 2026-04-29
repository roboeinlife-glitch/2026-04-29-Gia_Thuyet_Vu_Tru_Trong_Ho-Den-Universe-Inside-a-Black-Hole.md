#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

const double PI = 3.14159265358979323846;

struct Point3D {
    double x, y, z;
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

struct Galaxy {
    Point3D position;
    Point3D originalPos;
    double orbitRadius;
    double orbitSpeed;
    double angle;
    double size;
    sf::Color color;
    string name;
    double distanceToBlackhole;
    bool insideBlackhole;
};

string generateGalaxyName(bool inside) {
    if (inside) {
        const string prefixes[] = {"Core", "Nucleus", "Singularity", "Quantum", "Void", "Heart", "Spark", "Ember"};
        const string suffixes[] = {"-X", "-A", "-Prime", "-Seed", "-Mini"};
        return prefixes[rand() % 8] + suffixes[rand() % 5];
    } else {
        const string prefixes[] = {"NGC", "Andromeda", "Milky Way", "Sombrero", "Whirlpool", "Pinwheel", "Sunflower", "Black Eye", "Cigar", "Tadpole"};
        const string suffixes[] = {"-X", "-A", "-B", " Prime", " Secundus", " Major", " Minor"};
        return prefixes[rand() % 10] + suffixes[rand() % 7];
    }
}

sf::Color generateGalaxyColor(bool inside) {
    if (inside) {
        // Màu trắng xanh, xanh trắng cho thiên hà trong hố đen
        int type = rand() % 3;
        if (type == 0) return sf::Color(200, 230, 255, 220);  // Xanh trắng
        if (type == 1) return sf::Color(150, 200, 255, 220);  // Xanh dương nhạt
        return sf::Color(220, 240, 255, 220);  // Trắng xanh
    } else {
        int r = 50 + rand() % 206;
        int g = 50 + rand() % 206;
        int b = 50 + rand() % 206;
        int type = rand() % 3;
        if (type == 0) { b = min(255, b + 80); g = min(255, g + 40); }
        else if (type == 1) { r = min(255, r + 80); }
        else { r = min(255, r + 60); b = min(255, b + 60); }
        return sf::Color(r, g, b, 200);
    }
}

Point3D gravitationalLens(const Point3D& pos, double blackholeMass = 500.0) {
    double dist = sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
    if (dist < 30) return Point3D(0, 0, 0);
    double strength = min(2.0, blackholeMass / (dist * dist));
    Point3D result = pos;
    result.x = pos.x * (1 + strength * 0.3);
    result.y = pos.y * (1 + strength * 0.3);
    result.z = pos.z * (1 + strength * 0.2);
    return result;
}

sf::Vector2f project(const Point3D& p, double distance, int screenW, int screenH) {
    double factor = distance / (distance + p.z);
    return sf::Vector2f(screenW / 2 + p.x * factor, screenH / 2 + p.y * factor);
}

Point3D rotate(const Point3D& p, double yaw, double pitch) {
    double cosY = cos(yaw), sinY = sin(yaw);
    double cosP = cos(pitch), sinP = sin(pitch);
    double x1 = p.x * cosY + p.z * sinY;
    double z1 = -p.x * sinY + p.z * cosY;
    double y1 = p.y;
    double y2 = y1 * cosP - z1 * sinP;
    double z2 = y1 * sinP + z1 * cosP;
    return Point3D(x1, y2, z2);
}

struct DepthPair {
    double z;
    size_t index;
    bool operator<(const DepthPair& other) const { return z < other.z; }
};

int main() {
    srand(time(NULL));

    int screenW = 1200, screenH = 800;
    sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Vu Tru Trong Ho Den - Black Hole Universe");
    window.setFramerateLimit(60);

    // === TẠO CÁC THIÊN HÀ BÊN NGOÀI ===
    vector<Galaxy> galaxies;
    int numOuterGalaxies = 100;

    for (int i = 0; i < numOuterGalaxies; i++) {
        Galaxy g;
        g.insideBlackhole = false;
        // Quỹ đạo xa hố đen hơn
        g.orbitRadius = 220 + rand() % 280;
        g.orbitSpeed = 0.2 + (rand() % 80) / 200.0;
        g.angle = (rand() % 360) * PI / 180;
        g.size = 3 + rand() % 8;
        g.color = generateGalaxyColor(false);
        g.name = generateGalaxyName(false);

        double radX = g.orbitRadius;
        double radY = g.orbitRadius * (0.5 + (rand() % 100) / 100.0);
        double radZ = g.orbitRadius * (0.3 + (rand() % 70) / 100.0);

        g.originalPos.x = cos(g.angle) * radX;
        g.originalPos.y = sin(g.angle) * radY;
        g.originalPos.z = sin(g.angle * 2) * radZ;
        g.position = g.originalPos;
        g.distanceToBlackhole = sqrt(g.position.x*g.position.x + g.position.y*g.position.y + g.position.z*g.position.z);

        galaxies.push_back(g);
    }

    // === TẠO CÁC THIÊN HÀ BÊN TRONG HỐ ĐEN (nhỏ, màu xanh trắng) ===
    int numInnerGalaxies = 35;
    for (int i = 0; i < numInnerGalaxies; i++) {
        Galaxy g;
        g.insideBlackhole = true;
        // Quỹ đạo nhỏ để nằm gọn trong lõi
        g.orbitRadius = 15 + rand() % 70;
        g.orbitSpeed = 0.3 + (rand() % 100) / 150.0;
        g.angle = (rand() % 360) * PI / 180;
        g.size = 1.5 + (rand() % 25) / 10.0;  // Size từ 1.5 đến 3.5
        g.color = generateGalaxyColor(true);
        g.name = generateGalaxyName(true);

        double radX = g.orbitRadius;
        double radY = g.orbitRadius * (0.5 + (rand() % 100) / 100.0);
        double radZ = g.orbitRadius * (0.3 + (rand() % 70) / 100.0);

        g.originalPos.x = cos(g.angle) * radX;
        g.originalPos.y = sin(g.angle) * radY;
        g.originalPos.z = sin(g.angle * 2) * radZ;
        g.position = g.originalPos;
        g.distanceToBlackhole = sqrt(g.position.x*g.position.x + g.position.y*g.position.y + g.position.z*g.position.z);

        galaxies.push_back(g);
    }

    // === HẠT BỤI VŨ TRỤ (giảm số lượng, tản rộng) ===
    vector<Point3D> dustParticles;
    for (int i = 0; i < 1000; i++) {
        double r = 80 + rand() % 450;
        double theta = (rand() % 360) * PI / 180;
        double phi = (rand() % 360) * PI / 180;
        dustParticles.push_back(Point3D(
            sin(theta) * cos(phi) * r,
            sin(theta) * sin(phi) * r * 0.8,
            cos(theta) * r * 0.6
        ));
    }

    // === BIẾN ĐIỀU KHIỂN ===
    double yaw = 0, pitch = 0;
    bool dragging = false;
    sf::Vector2i lastMouse;
    double distance = 550;
    bool autoRotate = true;
    float time = 0;

    // Điều khiển góc nhìn cho thiên hà bên trong
    bool shiftPressed = false;
    double innerYaw = 0, innerPitch = 0;
    sf::Vector2i lastInnerMouse;

    // === FONT ===
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Khong load duoc font" << endl;
    }

    // === HỐ ĐEN DẠNG BẦU DỤC (Ellipse) ===
    // Thay vì circle, dùng sprite scale để tạo ellipse
    sf::CircleShape eventHorizon(140);
    eventHorizon.setFillColor(sf::Color::Transparent);
    eventHorizon.setOutlineColor(sf::Color(255, 40, 20, 200));
    eventHorizon.setOutlineThickness(4);
    eventHorizon.setOrigin(140, 140);

    sf::CircleShape lightBend1(165);
    lightBend1.setFillColor(sf::Color::Transparent);
    lightBend1.setOutlineColor(sf::Color(255, 60, 30, 120));
    lightBend1.setOutlineThickness(3);
    lightBend1.setOrigin(165, 165);

    sf::CircleShape lightBend2(195);
    lightBend2.setFillColor(sf::Color::Transparent);
    lightBend2.setOutlineColor(sf::Color(255, 80, 40, 80));
    lightBend2.setOutlineThickness(2.5);
    lightBend2.setOrigin(195, 195);

    sf::CircleShape lightBend3(230);
    lightBend3.setFillColor(sf::Color::Transparent);
    lightBend3.setOutlineColor(sf::Color(255, 100, 50, 50));
    lightBend3.setOutlineThickness(2);
    lightBend3.setOrigin(230, 230);

    sf::CircleShape accretionDisk(270);
    accretionDisk.setFillColor(sf::Color(255, 80, 30, 20));
    accretionDisk.setOutlineColor(sf::Color(255, 120, 50, 50));
    accretionDisk.setOutlineThickness(3);
    accretionDisk.setOrigin(270, 270);

    sf::CircleShape glowRegion(340);
    glowRegion.setFillColor(sf::Color(255, 60, 20, 10));
    glowRegion.setOutlineColor(sf::Color(255, 80, 30, 25));
    glowRegion.setOutlineThickness(2);
    glowRegion.setOrigin(340, 340);

    // === TEXT ===
    sf::Text infoText, helpText, statusText, innerText;
    infoText.setFont(font); infoText.setCharacterSize(16); infoText.setFillColor(sf::Color::Yellow); infoText.setPosition(10, 10);
    helpText.setFont(font); helpText.setCharacterSize(12); helpText.setFillColor(sf::Color::Cyan); helpText.setPosition(10, screenH-80);
    statusText.setFont(font); statusText.setCharacterSize(12); statusText.setFillColor(sf::Color::White); statusText.setPosition(10, screenH-40);
    innerText.setFont(font); innerText.setCharacterSize(13); innerText.setFillColor(sf::Color(100, 200, 255)); innerText.setPosition(10, screenH-115);

    helpText.setString("Chuot trai: Xoay | Shift+Chuot: Dieu khien goc nhin thien ha trong | Cuon chuot: Zoom | Space: Tu dong xoay");
    infoText.setString("HO DEN - " + to_string(numInnerGalaxies) + " thien ha nho (xanh trang) nam ben trong long den");
    innerText.setString(">>> " + to_string(numInnerGalaxies) + " THIEN HA BEN TRONG HO DEN - MAU XANH TRANG <<<");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Xoay toàn cảnh
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !shiftPressed) {
                dragging = true;
                lastMouse = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
            }
            if (event.type == sf::Event::MouseMoved && dragging && !shiftPressed) {
                sf::Vector2i newMouse = sf::Mouse::getPosition(window);
                yaw -= (newMouse.x - lastMouse.x) * 0.005;
                pitch += (newMouse.y - lastMouse.y) * 0.005;
                if (pitch > PI/2.2) pitch = PI/2.2;
                if (pitch < -PI/2.2) pitch = -PI/2.2;
                lastMouse = newMouse;
            }

            // Điều khiển góc nhìn thiên hà bên trong
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)) {
                shiftPressed = true;
            }
            if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)) {
                shiftPressed = false;
                dragging = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shiftPressed) {
                dragging = true;
                lastInnerMouse = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseMoved && dragging && shiftPressed) {
                sf::Vector2i newMouse = sf::Mouse::getPosition(window);
                innerYaw -= (newMouse.x - lastInnerMouse.x) * 0.008;
                innerPitch += (newMouse.y - lastInnerMouse.y) * 0.008;
                if (innerPitch > PI/3.0) innerPitch = PI/3.0;
                if (innerPitch < -PI/3.0) innerPitch = -PI/3.0;
                lastInnerMouse = newMouse;
            }

            // Zoom
            if (event.type == sf::Event::MouseWheelScrolled) {
                distance -= event.mouseWheelScroll.delta * 30;
                if (distance < 250) distance = 250;
                if (distance > 900) distance = 900;
            }

            // Click phải
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                bool found = false;
                for (size_t i = 0; i < galaxies.size(); i++) {
                    Point3D rotatedPos = rotate(galaxies[i].position, yaw, pitch);
                    sf::Vector2f screenPos = project(rotatedPos, distance, screenW, screenH);
                    float dx = mousePos.x - screenPos.x;
                    float dy = mousePos.y - screenPos.y;
                    if (sqrt(dx*dx + dy*dy) <= galaxies[i].size + 5) {
                        string location = galaxies[i].insideBlackhole ? "BEN TRONG HO DEN" : "BEN NGOAI HO DEN";
                        infoText.setString(galaxies[i].name + " (" + location + ") | Kich thuoc: " + to_string((int)galaxies[i].size));
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    infoText.setString("Khong co thien ha tai vi tri nay");
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                autoRotate = !autoRotate;
            }
        }

        if (autoRotate) yaw += 0.0015;
        time += 0.02;

        // Cập nhật tất cả thiên hà
        for (size_t i = 0; i < galaxies.size(); i++) {
            galaxies[i].angle += galaxies[i].orbitSpeed * 0.015;
            if (galaxies[i].angle > 2*PI) galaxies[i].angle -= 2*PI;

            double radX = galaxies[i].orbitRadius;
            double radY = galaxies[i].orbitRadius * 0.7;
            double radZ = galaxies[i].orbitRadius * 0.4;

            galaxies[i].originalPos.x = cos(galaxies[i].angle) * radX;
            galaxies[i].originalPos.y = sin(galaxies[i].angle) * radY;
            galaxies[i].originalPos.z = sin(galaxies[i].angle * 1.5) * radZ;

            if (!galaxies[i].insideBlackhole) {
                // Thiên hà bên ngoài - có thể bị hút vào thỉnh thoảng
                // Chỉ một số ít (khoảng 5%) bị ảnh hưởng lực hút đáng kể
                if (rand() % 100 < 3) {
                    galaxies[i].position = gravitationalLens(galaxies[i].originalPos);
                } else {
                    galaxies[i].position = galaxies[i].originalPos;
                }
            } else {
                // Thiên hà bên trong - chịu ảnh hưởng của innerYaw/ innerPitch
                double yawEffect = innerYaw;
                double pitchEffect = innerPitch;
                galaxies[i].position.x = galaxies[i].originalPos.x * cos(yawEffect) + galaxies[i].originalPos.z * sin(yawEffect);
                galaxies[i].position.z = -galaxies[i].originalPos.x * sin(yawEffect) + galaxies[i].originalPos.z * cos(yawEffect);
                galaxies[i].position.y = galaxies[i].originalPos.y + pitchEffect * 20;
            }

            galaxies[i].distanceToBlackhole = sqrt(galaxies[i].position.x*galaxies[i].position.x +
                                                  galaxies[i].position.y*galaxies[i].position.y +
                                                  galaxies[i].position.z*galaxies[i].position.z);
        }

        // Cập nhật hạt bụi
        for (size_t i = 0; i < dustParticles.size(); i++) {
            dustParticles[i].x += (rand() % 3 - 1) * 0.3;
            dustParticles[i].y += (rand() % 3 - 1) * 0.3;
            dustParticles[i].z += (rand() % 3 - 1) * 0.3;
            double r = sqrt(dustParticles[i].x*dustParticles[i].x + dustParticles[i].y*dustParticles[i].y + dustParticles[i].z*dustParticles[i].z);
            if (r > 500) {
                dustParticles[i].x = (rand() % 1000 - 500) / 2.0;
                dustParticles[i].y = (rand() % 1000 - 500) / 2.0;
                dustParticles[i].z = (rand() % 1000 - 500) / 2.0;
            }
        }

        window.clear(sf::Color(3, 3, 15));

        // === VẼ SAO NỀN ===
        for (int i = 0; i < 300; i++) {
            int x = (rand() % screenW), y = (rand() % screenH);
            sf::RectangleShape star(sf::Vector2f(1.2, 1.2));
            star.setFillColor(sf::Color(255, 255, 255, 30 + rand() % 100));
            star.setPosition(x, y);
            window.draw(star);
        }

        // === VẼ HẠT BỤI ===
        for (size_t i = 0; i < dustParticles.size(); i++) {
            Point3D rotatedDust = rotate(dustParticles[i], yaw, pitch);
            sf::Vector2f dustPos = project(rotatedDust, distance, screenW, screenH);
            sf::CircleShape dustPixel(0.8);
            int brightness = 100 + rand() % 155;
            dustPixel.setFillColor(sf::Color(brightness, brightness, brightness, 40 + rand() % 80));
            dustPixel.setPosition(dustPos);
            window.draw(dustPixel);
        }

        // === SẮP XẾP VÀ VẼ THIÊN HÀ ===
        vector<DepthPair> depthOrder;
        for (size_t i = 0; i < galaxies.size(); i++) {
            Point3D rotatedPos = rotate(galaxies[i].position, yaw, pitch);
            DepthPair dp;
            dp.z = rotatedPos.z;
            dp.index = i;
            depthOrder.push_back(dp);
        }
        sort(depthOrder.begin(), depthOrder.end());

        for (size_t j = 0; j < depthOrder.size(); j++) {
            size_t idx = depthOrder[j].index;
            const Galaxy& galaxy = galaxies[idx];
            Point3D rotatedPos = rotate(galaxy.position, yaw, pitch);
            sf::Vector2f screenPos = project(rotatedPos, distance, screenW, screenH);

            // Glow cho thiên hà (thiên hà trong sáng hơn)
            if (galaxy.insideBlackhole) {
                sf::CircleShape glow(galaxy.size + 3);
                glow.setFillColor(sf::Color(galaxy.color.r, galaxy.color.g, galaxy.color.b, 120));
                glow.setOrigin(glow.getRadius(), glow.getRadius());
                glow.setPosition(screenPos);
                window.draw(glow);
            } else {
                sf::CircleShape glow(galaxy.size + 4);
                glow.setFillColor(sf::Color(galaxy.color.r, galaxy.color.g, galaxy.color.b, 40));
                glow.setOrigin(glow.getRadius(), glow.getRadius());
                glow.setPosition(screenPos);
                window.draw(glow);
            }

            // Vẽ thiên hà
            sf::CircleShape galaxyShape(galaxy.size);
            galaxyShape.setFillColor(galaxy.color);
            galaxyShape.setOrigin(galaxy.size, galaxy.size);
            galaxyShape.setPosition(screenPos);
            window.draw(galaxyShape);

            // Lõi sáng
            sf::CircleShape core(galaxy.size * 0.4);
            core.setFillColor(sf::Color(255, 255, 220, 200));
            core.setOrigin(core.getRadius(), core.getRadius());
            core.setPosition(screenPos);
            window.draw(core);
        }

        // === VẼ CÁC VÒNG HỐ ĐEN (dạng bầu dục bằng scale) ===
        sf::Vector2f center(screenW/2, screenH/2);

        // Tạo hiệu ứng ellipse bằng cách scale các circle
        auto drawEllipse = [&](sf::CircleShape& shape, float scaleX, float scaleY, float rotation) {
            shape.setPosition(center);
            shape.setScale(scaleX, scaleY);
            shape.setRotation(rotation);
            window.draw(shape);
            shape.setScale(1, 1); // Reset scale
        };

        // Vùng phát sáng rộng
        glowRegion.setPosition(center);
        glowRegion.setRotation(glowRegion.getRotation() + 0.2);
        glowRegion.setScale(1.2, 0.7);
        window.draw(glowRegion);
        glowRegion.setScale(1, 1);

        // Đĩa bồi tụ
        accretionDisk.setPosition(center);
        accretionDisk.setRotation(accretionDisk.getRotation() + 0.6);
        accretionDisk.setScale(1.15, 0.65);
        window.draw(accretionDisk);
        accretionDisk.setScale(1, 1);

        // Vòng bẻ cong ánh sáng
        lightBend3.setPosition(center);
        lightBend3.setRotation(lightBend3.getRotation() + 0.3);
        lightBend3.setScale(1.1, 0.68);
        window.draw(lightBend3);
        lightBend3.setScale(1, 1);

        lightBend2.setPosition(center);
        lightBend2.setRotation(lightBend2.getRotation() - 0.4);
        lightBend2.setScale(1.08, 0.7);
        window.draw(lightBend2);
        lightBend2.setScale(1, 1);

        lightBend1.setPosition(center);
        lightBend1.setRotation(lightBend1.getRotation() + 0.5);
        lightBend1.setScale(1.05, 0.72);
        window.draw(lightBend1);
        lightBend1.setScale(1, 1);

        // Chân trời sự kiện
        eventHorizon.setPosition(center);
        eventHorizon.setRotation(eventHorizon.getRotation() + 0.2);
        eventHorizon.setScale(1.02, 0.75);
        window.draw(eventHorizon);
        eventHorizon.setScale(1, 1);

        // === TEXT ===
        window.draw(infoText);
        window.draw(helpText);
        window.draw(innerText);

        string status = "Tu dong xoay: " + string(autoRotate ? "BAT" : "TAT");
        status += " | Zoom: " + to_string((int)((900 - distance) / 6)) + "%";
        status += " | Thien ha trong ho den: " + to_string(numInnerGalaxies);
        status += " | Shift: " + string(shiftPressed ? "DANG DIEU KHIEN" : "NGUNG");
        statusText.setString(status);
        window.draw(statusText);

        window.display();
    }

    return 0;
}
