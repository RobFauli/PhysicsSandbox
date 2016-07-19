#include "SimulationConfigurations.hpp"

// Needs changing as Triangles no longer can hold multiple poisitions (or copies) in one object.

/*
std::unique_ptr<Triangles> testTriangles(const Shader &shader, const std::vector<glm::vec3> positions) {
    std::vector<GLfloat> vertices{
        //Pos               //Color
        1.0f, 0.f, 0.f,     1.0f, 0.5f, 0.3f,
        -1.f, 0.f, 0.f,     0.5f, 0.3f, 1.0f,
        0.f, 1.f, 0.f,      0.3f, 1.0f, 0.5f,
        0.f, -1.f, 0.f,     1.0f, 0.5f, 0.3f,
        0.f, 0.f, 1.f,      0.5f, 0.3f, 1.f,
        0.f, 0.f, -1.f,     0.3f, 1.f, 0.5f
    };

    std::vector<GLuint> indices{
        // triangles with z = 1 as one vertice:
        4, 0, 2,
        4, 0, 3,
        4, 1, 2,
        4, 1, 3,
        5, 0, 2,
        5, 0, 3,
        5, 1, 2,
        5, 1, 3
    };

    return std::make_unique<Triangles>(Triangles(vertices, indices, &shader, positions));
}

void coldCollapseSimulation()
{
    Vector3<double> nullV3;
    Simulation testSim;
    auto GForce = std::make_shared<GravitationalForce>(GravitationalForce());
    GForce->setSoftener(0.15*0.15);
    std::shared_ptr<Force> force = GForce;
    testSim.addForce(force);
    std::unique_ptr<ODESolver> leapfrog_ptr = std::make_unique<Leapfrog>(Leapfrog());
    testSim.changeODESolver(move(leapfrog_ptr));

    testSim.changeTimeUnitsTo("yr");
    testSim.changeLenghtUnitsTo("ly");

    double dt = 1e4;
    testSim.setDT(dt);
    //testSim.setSaveDataEveryXIteration(1);

    auto M = g_sun_mass_SI;
    auto r_max = 20.0;
    auto N = 200u;

    auto coords = uniformRandomSpherePositions(r_max, N);

    for (auto k = 0u; k<N; ++k)
        testSim.addPointParticle(M, 0, coords[k], nullV3);

    int maxInt = 1e4;

    std::vector<decltype(testSim.getAllPositions())> posHist;
    int i = 0;
    while (i<maxInt) {
        posHist.push_back(testSim.getAllPositions());
        testSim.runOneTimeStep();
        ++i;
    }

    //std::ofstream ofile("test.dat");
    //ofile << testSim.getData().str();
    //ofile.close();

    std::cout << "Simulation finished, import 'show' to display: " << std::endl;
    std::__cxx11::string str;
    while (std::cin >> str) {
        if (str == "show")
            break;
        else
        {}
    }

    Window window(800, 600, "test", {0.f, 0.f, 0.f, 1.f});
    Shader shader("../../Visualization/Shaders/TrianglesVertexShader.glsl",
                  nullptr,
                  "../../Visualization/Shaders/TrianglesFragmentShader.glsl");

    std::unique_ptr<Triangles> triangle_ptr = testTriangles(shader, {});

    Shape* shape_ptr = &*triangle_ptr;
    window.getRenderer().addObject(shape_ptr);

    triangle_ptr->resizeByFactor(0.03);
    triangle_ptr->Setup();

    i = 0;
    while (!window.WindowShouldClose()) {
        if (i % 100 == 0) {
            usleep(1e4);
            if (i<maxInt) {
                std::vector<glm::vec3> positions;
                double max = r_max;
                for (auto &position : posHist[i]) {
                    positions.push_back({position.x / max, position.y / max,
                                         position.z / max});
                }
                triangle_ptr->setPosition(positions);
            }
            window.GameLoop();
        }
        else { }
        ++i;
    }
    window.CloseWindow();
}
 */