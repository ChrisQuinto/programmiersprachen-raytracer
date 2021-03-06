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
#include "renderer.hpp"

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

    std::string b = "Box3";
    Material mat{};
    Box box3{glm::vec3{1.0,1.0,1.0}, glm::vec3{2.0,2.0,2.0}, b, mat};
    REQUIRE(box3.name() == b);
    REQUIRE(box3.material() == mat);
    std::cout << box3;
}

TEST_CASE("test sphere", "[test sphere]")
{
    std::cout << "Sphere Tests: " << std::endl;

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
    std::cout << "Intersect-Ray-Sphere Tests: " << std::endl;

    glm::vec3 ray_origin0(1.0,1.0,1.0);
    glm::vec3 ray_direction0(-0.9,-0.9,-0.9);
    Ray ray0{ray_origin0,ray_direction0};

    glm::vec3 ray_origin1(0.0,0.0,0.0);
    glm::vec3 ray_direction1(0.0,0.0,1.0);
    Ray ray1{ray_origin1,ray_direction1};

    glm::vec3 ray_origin2(1.0,1.0,1.0);
    glm::vec3 ray_direction2(1.1,1.1,1.1);
    Ray ray2{ray_origin2,ray_direction2};

    float sphere_radius0(1.0);
    Material mat{};
    glm::vec3 sphere_center0(0.0,0.0,5.0);
    std::string a = "sphere0";
    Sphere sphere0{sphere_center0, sphere_radius0, a, mat};

    glm::vec3 sphere_center1(3.0,1.5,4.5);
    std::string b = "sphere1";
    Sphere sphere1{sphere_center1, sphere_radius0, b, mat};

    glm::vec3 sphere_center2(7.0,7.0,7.0);
    std::string c = "sphere2";
    Sphere sphere2{sphere_center2, sphere_radius0, c, mat};

    glm::vec3 sphere_center3(1.0,1.0,1.0);
    std::string d = "sphere3";
    Sphere sphere3{sphere_center3, sphere_radius0, d, mat};

    Hit s_hit0 = sphere0.intersect(ray1);
    std::cout << s_hit0;
    Hit s_hit1 = sphere1.intersect(ray1);
    std::cout << s_hit1;
    Hit s_hit2 = sphere2.intersect(ray2);
    std::cout << s_hit2;
    Hit s_hit3 = sphere3.intersect(ray0);
    std::cout << s_hit3;
    REQUIRE(s_hit0.hit_ == true);
    REQUIRE(s_hit1.hit_ == false);
    REQUIRE(s_hit2.hit_ == true);
    REQUIRE(s_hit3.hit_ == true);
}

TEST_CASE("test intersectRayBox", "[test intersectRayBox]")
{
    std::cout << std::endl << "Intersect-Ray-Box Tests: " << std::endl;

    glm::vec3 ray_origin0(0.0,0.0,0.0);
    glm::vec3 ray_direction0(1.0,1.0,1.0);
    Ray ray0{ray_origin0,ray_direction0};

    glm::vec3 ray_origin1(3.0,1.5,4.5);
    glm::vec3 ray_direction1(-1.0,-1.0,-1.0);
    Ray ray1{ray_origin1,ray_direction1};

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

    Hit b_hit0 = box0.intersect(ray0);
    std::cout << b_hit0;
    Hit b_hit1 = box0.intersect(ray1);
    std::cout << b_hit1;
    Hit b_hit2 = box1.intersect(ray0);
    std::cout << b_hit2;
    Hit b_hit3 = box1.intersect(ray1);
    std::cout << b_hit3;
    Hit b_hit4 = box2.intersect(ray0);
    std::cout << b_hit4;
    Hit b_hit5 = box2.intersect(ray1);
    std::cout << b_hit5;
    REQUIRE(b_hit0.hit_ == true);
    REQUIRE(b_hit1.hit_ == false);
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

/*TEST_CASE("sdfloader_material", "[sdfloader]"){
    Sdfloader loader{"./materials.txt"};
    std::shared_ptr<Scene> s = loader.loadscene("./materials.txt");
}*/

/*TEST_CASE("sdfloader Test", "[sdfloader test]"){
    Sdfloader loader{"./test.txt"};
    std::shared_ptr<Scene> sptr = loader.loadscene("./test.txt");
    Scene s = *sptr;
    std::cout << "\n" ;
    std::cout << "Ambientes Licht: \n" << s.amblight << std::endl;
    std::cout << "Background-Color: \n" << s.background << std::endl;
    std::cout << *s.materials["red"] << std::endl;
    std::cout << *s.materials["blue"] << std::endl;

    for (std::vector<std::shared_ptr<Shape>>::iterator i = sptr->shapes_ptr.begin(); i != sptr->shapes_ptr.end(); ++i){
        std::cout << *(*i);
    }
    //std::cout << s.camera;
    //std::cout << *s.lights[0];
}*/

TEST_CASE("renderer Test", "[renderer test]"){
    Sdfloader loader{"./test.txt"};
    std::shared_ptr<Scene> s = loader.loadscene("./test.txt");
    Renderer renderer(s);
    renderer.render();
}

/*TEST_CASE("animation Test", "[animation test]"){
    Sdfloader loader{"./test.txt"};
    std::shared_ptr<Scene> s = loader.loadscene("./test.txt");

    std::string n = "batlight";
    Color c{1.0,1.0,1.0};
    int j = -200;
    for (int i = 0; i < 80; ++i)
    {
        glm::vec3 pos{j,100,-2500};
        std::shared_ptr<Light> lightptr = std::make_shared<Light>(Light{n,pos,c});

        s->filename = "batframeb" + std::to_string(i) + ".ppm";
        s->lights.clear();
        s->lights.push_back(lightptr);

        Renderer renderer(s);
        renderer.render();

        std::cout << "\nbatframe" << i << "done.\n";

        j += 5;
    }
}*/


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
