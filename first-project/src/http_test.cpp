#include <iostream>
#include <string>
#include <curl/curl.h>

class RestClient {
public:
    RestClient(const std::string& apiUrl) : apiUrl(apiUrl) {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    ~RestClient() {
        curl_global_cleanup();
    }

    std::string get(const std::string& endpoint) {
        std::string responseData;
        std::string url = apiUrl + endpoint;

        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "Error en la consulta HTTP: " << curl_easy_strerror(res) << std::endl;
            }

            curl_easy_cleanup(curl);
        }

        return responseData;
    }

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        size_t totalSize = size * nmemb;
        std::string* response = static_cast<std::string*>(userp);
        response->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    std::string apiUrl;
};

int main() {
    RestClient client("https://jsonplaceholder.typicode.com");
    std::string endpoint = "/todos/1";
    std::string response = client.get(endpoint);

    std::cout << "Respuesta de la API:\n" << response << std::endl;

    return 0;
}
