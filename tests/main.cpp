#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
// #include <glm/glm.hpp>
// #include <glm/gtx/intersect.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "sdfloader.hpp"


TEST_CASE("test material", "[test material]")
{
    std::cout << std::endl << "Material Tests: " << std::endl;

    std::cout << "(Default-Konstructor)" <<std::endl;
    Material mat1;
    std::string s1 = "defaultmaterial";
    Color col1{};
    REQUIRE(mat1.name() == s1);
    REQUIRE(mat1.ka() == col1);
    REQUIRE(mat1.kd() == col1);
    REQUIRE(mat1.ks() == col1);
    REQUIRE(mat1.m() == 0);
    std::cout << mat1;

    std::cout << std::endl << "(Konstructor)" << std::endl;
    std::string s2 = "mat2";
    Color col2{1.0f,0.0f,1.0f};
    Material mat2{s2,col2,col2,col2,1};
    REQUIRE(mat2.name() == s2);
    REQUIRE(mat2.ka() == col2);
    REQUIRE(mat2.kd() == col2);
    REQUIRE(mat2.ks() == col2);
    REQUIRE(mat2.m() == 1);
    std::cout << mat2;
}

TEST_CASE("test box", "[test box]")
{
    std::cout << std::endl << "Box Tests: " << std::endl;

    Box box1;
    glm::vec3 vec3{};
    REQUIRE(box1.min() == vec3);
    REQUIRE(box1.max() == vec3);

    Box box2{glm::vec3{1.0,1.0,1.0},glm::vec3{3.0,4.0,5.0}};
    glm::vec3 p1{1.0,1.0,1.0};
    glm::vec3 p2{3.0,4.0,5.0};
    REQUIRE(box2.min() == p1);
    REQUIRE(box2.max() == p2);
    REQUIRE(box2.area() == Approx(52.0));
    REQUIRE(box2.volume() == Approx(24.0));

    std::cout << std::endl;
    std::string b = "Box3";
    Material mat{};
    Box box3{glm::vec3{1.0,1.0,1.0}, glm::vec3{2.0,2.0,2.0}, b, mat};
    REQUIRE(box3.name() == b);
    REQUIRE(box3.material() == mat);
    std::cout << box3;
}

TEST_CASE("test sphere", "[test sphere]")
{
    std::cout << std::endl << "Sphere Tests: " << std::endl;

    Sphere sphere0;
    glm::vec3 vec0{};
    std::string a = "defaultshape";
    Material mat{};
    REQUIRE(sphere0.radius() == Approx(0.0));
    REQUIRE(sphere0.center() == vec0);
    REQUIRE(sphere0.name() == a);
    REQUIRE(sphere0.material() == mat);
    std::cout << sphere0;

    glm::vec3 vec1{1.0,1.0,1.0};
    std::string b = "sphere1";
    Sphere sphere1{vec1, 1.0, b, mat};
    REQUIRE(sphere1.radius() == Approx(1.0));
    REQUIRE(sphere1.center() == vec1);
    REQUIRE(sphere1.name() == b);
    REQUIRE(sphere1.material() == mat);
    REQUIRE(sphere1.area() == Approx(12.5664));
    REQUIRE(sphere1.volume() == Approx(4.18879f));
    std::cout << sphere1;
}

TEST_CASE("test intersectRaySphere", "[test intersectRaySphere]")
{
    std::cout << std::endl << "Intersect-Ray-Sphere Tests: " << std::endl;

    glm::vec3 ray_origin1(0.0,0.0,0.0);
    glm::vec3 ray_direction1(0.0,0.0,1.0);
    Ray ray1{ray_origin1,ray_direction1};

    glm::vec3 ray_origin2(2.0,1.0,3.0);
    glm::vec3 ray_direction2(4.0,2.0,6.0);
    Ray ray2{ray_origin2,ray_direction2};

    float sphere_radius(1.0);
    Material mat{};
    glm::vec3 sphere_center0(0.0,0.0,5.0);
    std::string a = "sphere0";
    Sphere sphere0{sphere_center0, sphere_radius, a, mat};

    glm::vec3 sphere_center1(3.0,1.5,4.5);
    std::string b = "sphere1";
    Sphere sphere1{sphere_center1, sphere_radius, b, mat};

    glm::vec3 sphere_center2(7.0,7.0,7.0);
    std::string c = "sphere2";
    Sphere sphere2{sphere_center2, sphere_radius, c, mat};

    float distance(0.0);
    REQUIRE(sphere0.intersect(ray1, distance) == true);
    REQUIRE(distance == Approx(4.0f));
    REQUIRE(sphere1.intersect(ray2, distance) == true);
    REQUIRE(sphere2.intersect(ray2, distance) == false);
}

TEST_CASE("test intersectRayBox", "[test intersectRayBox]")
{
    std::cout << std::endl << "Intersect-Ray-Box Tests: " << std::endl;

    glm::vec3 ray_origin1(0.0,0.0,0.0);
    glm::vec3 ray_direction1(1.0,1.0,1.0);
    Ray ray1{ray_origin1,ray_direction1};

    glm::vec3 ray_origin2(3.0,1.5,4.5);
    glm::vec3 ray_direction2(-1.0,-1.0,-1.0);
    Ray ray2{ray_origin2,ray_direction2};

    std::string a = "box0";
    Material mat{};
    glm::vec3 box_min0(2.0,2.0,2.0);
    glm::vec3 box_max0(4.0,4.0,4.0);
    Box box0{box_min0, box_max0, a, mat};

    std::string b = "box1";
    glm::vec3 box_min1(3.0,1.5,4.5);
    glm::vec3 box_max1(1.0,1.0,1.0);
    Box box1{box_min1, box_max1, b, mat};

    std::string c = "box2";
    glm::vec3 box_min2(7.0,7.0,7.0);
    glm::vec3 box_max2(6.0,8.0,6.0);
    Box box2{box_min2, box_max2, c, mat};

	Hit temp;
	REQUIRE(box0.intersect(ray1) == temp);
	REQUIRE(box1.intersect(ray2) == temp);
	REQUIRE(box2.intersect(ray2) == temp);
}

TEST_CASE("test light", "[test light]"){
    std::cout << std::endl << "Light Tests: " << std::endl;

    std::cout << "(Default-Konstructor)" <<std::endl;
    Light light1;
    std::string s1 = "defaultlight";
    glm::vec3 pos0(0.0,0.0,0.0);
    Color c0;
    REQUIRE(light1.name() == s1);
    REQUIRE(light1.pos() == pos0);
    REQUIRE(light1.dl() == c0);
    std::cout << light1;
}

TEST_CASE("test camera", "[test camera]"){
    std::cout << "Camera Tests: " << std::endl;

    std::cout << "(Default-Konstructor)" <<std::endl;
    Camera cam1;
    std::string s1 = "defaultcam";
    glm::vec3 pos0(0.0,0.0,0.0);
    float fovx = 60.0f;
    REQUIRE(cam1.name() == s1);
    REQUIRE(cam1.pos() == pos0);
    REQUIRE(cam1.fovx() == fovx);
    std::cout << cam1;
    glm::vec3 d(1.0,1.0,1.0);
    //std::cout << cam1.castray(d) << std::endl;
}

TEST_CASE("sdfloader_material", "[sdfloader]"){
    Sdfloader loader{"./materials.txt"};
    Scene s = loader.loadscene("./materials.txt");
}

TEST_CASE("sdfloader Test", "[sdfloader test]"){
    Sdfloader loader{"./test.txt"};
    Scene s = loader.loadscene("./test.txt");
    std::cout << "\n" ;
    std::cout << "Ambientes Licht: \n" << s.amblight << std::endl;
    std::cout << "Background-Color: \n" << s.background << std::endl;
    std::cout << *s.materials["red"] << std::endl;
    std::cout << *s.materials["blue"] << std::endl;
    std::cout << *s.shapes_ptr[0];
    std::cout << *s.shapes_ptr[1];
    std::cout << s.camera;
    std::cout << *s.lights[0];
}



// AUFGABENBLATT 6
/*TEST_CASE("statischer Typ/dynamischer Typ Variable", "[6.7]")
{
    std::cout << std::endl << "6.7:" << std::endl;

    Color  rot(255,0,0);
    Material red("ton" ,rot,rot,rot,7.1f);
    glm::vec3 position(0,0,0);

    std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>(
        position, 1.2, "sphere0", red
    );

    std::shared_ptr<Shape> s2 = std::make_shared<Sphere>(
        position, 1.2, "sphere1", red
    );

    s1->print(std::cout);
    s2->print(std::cout);

    //C++ ist eine statisch typisierte Sprache.
    //In C++ können Variablen einer Basisklasse Objekte einer abgeleiteten Klasse referenzieren.
    //Da hier im Beispiel die Pointer von verschiedenen Typen sind, kann man sehen, dass diese trotzdem auf das gleiche Objekt zeigen können.
    //Der erste erzeugte Sphere-Pointer zeigt auf eine Sphere, hier sind statische und dynamische Klasse die selbe.
    //Der zweite erzeugte Shape-Pointer zeigt auf eine Sphere, hier ist Shape die statische und Sphere ist die dynamische Klasse.
}

TEST_CASE("destructor", "[6.8]")
{
    std::cout << std::endl << "6.8:" << std::endl;


    Material red("red",Color {255,0,0}, 0.0);
    glm::vec3 position(0,0,0);

    Sphere* s1 = new Sphere(position, 1.2f, "sphere0", red);
    Shape* s2 = new Sphere(position, 1.2f, "sphere1", red);

    s1->print(std::cout);
    s2->print(std::cout);

    delete s1;
    delete s2;

    //Ohne virtual wird beim Shape-Pointer der Destruktor der Sphere nicht aufgerufen, da hier nur der Destruktor von der Klasse aufgerufen wird auf den der Pointer zeigt.
    //Bei dem Sphere-Pointer werden zwei Destruktoren aufgerufen, da wenn der Destruktor der Sphere aufgerufen wird, auf welche der Pointer zeigt, automatisch auch noch der Destruktor der Basisklasse aufgerufen wird.
    //Wenn man virtual verwendet wird auch für den Shape-Pointer der Destruktor der Sphere-Klasse aufgerufen, da der Destruktor des Pointers virtual und Sphere die abgeleitete Klasse der Basisklasse Shape ist.
}*/

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
