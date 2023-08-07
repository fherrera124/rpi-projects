#include <iostream>
#include <thread>
#include <mutex>

class Resource {
public:
    void useResource(int id) {
        std::lock_guard<std::mutex> lock(resourceMutex);  // Bloquea el recurso

        std::cout << "Thread " << id << " está usando el recurso." << std::endl;
        // Simula un uso del recurso
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "Thread " << id << " ha terminado de usar el recurso." << std::endl;
    }

private:
    std::mutex resourceMutex;
};

class ThreadWorker {
public:
    ThreadWorker(int id, Resource& res) : id(id), resource(res) {} // {} está vacío porque toda la inicialización se ha realizado en la lista de inicialización.

    void operator()() { //Function Call Operator
        resource.useResource(id);
    }

private:
    int id;
    Resource& resource;
};

int main() {
    Resource sharedResource;

    std::thread thread1(ThreadWorker(1, sharedResource));
    std::thread thread2(ThreadWorker(2, sharedResource));

    thread1.join();
    thread2.join();

    return 0;
}
