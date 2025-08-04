#pragma once

#include <string>

class FirebaseObject
{
private:
    std::string api_key;
    std::string project_id;
    std::string app_id;

public:
    FirebaseObject(const std::string& api_key, const std::string& project_id, const std::string& app_id)
        : api_key(api_key), project_id(project_id), app_id(app_id) {}

    void setApiKey(const std::string& api_key) {
        this->api_key = api_key;
    }

    std::string getApiKey() const {
        return api_key;
    }

    void setProjectID(const std::string& project_id){
        this->project_id = project_id;
    }

    std::string getProjectID() const {
        return project_id;
    }

    void setAppID(const std::string& app_id) {
        this->app_id = app_id;
    }

    std::string getAppID() const {
        return app_id;
    }
};
