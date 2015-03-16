#pragma once

#include "declarations.h"

#include <curl/curl.h>

#include <set>
#include <string>

namespace lf {

/**
 * @class engine
 * @brief API for liquidfiles.
 * 
 *        engine is main class to do operations with liquidfiles.
 *        It provides interface to send, receive files and other operations
 *        supported by liquidfiles.
 */
class engine
{
public:
    /// @brief Constructor.
    engine();

    /// @brief Destructor.
    ~engine();

private:
    engine(const engine&);
    engine& operator=(const engine&);

    /// @name API
    /// @{
public:
    typedef std::set<std::string> files;

public:
    /**
     * @brief Sends the file to specified user, by specified server.
     * @param server Server URL.
     * @param user User name or email.
     * @param key API Key of Liquidfiles.
     * @param subject Subject of composed email.
     * @param message Message body of email.
     * @param fs Files list to send.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error, upload_error, send_error.
     */
    std::string send(std::string server,
            const std::string& user, 
            const std::string& key,
            const std::string& subject,
            const std::string& message,
            const files& fs,
            report_level s,
            validate_cert v);

    /**
     * @brief Lists all the messages.
     * @param server Server URL.
     * @param key API Key of Liquidfiles.
     * @param l Hours, to get messages from the last specified hours.
     * @param f Date, to get messages from that date.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @param f Format of output (table or csv).
     * @throw curl_error.
     */
    void messages(std::string server,
            const std::string& key,
            const std::string& l,
            const std::string& f,
            report_level s,
            validate_cert v,
            output_format of);

    /**
     * @brief List the given message.
     * @param server Server URL.
     * @param key API Key of Liquidfiles.
     * @param id Message id.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @param f Format of output (table or csv).
     * @throw curl_error.
     */
    void message(std::string server,
            const std::string& key,
            const std::string& id,
            report_level s,
            validate_cert v,
            output_format f);

    /**
     * @brief Downloads the files from the given urls.
     * @param urls URLs of the files.
     * @param path Path to output directory.
     * @param key API Key of Liquidfiles.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     */
    void download(const std::set<std::string>& urls,
            const std::string& path,
            const std::string& key,
            report_level s,
            validate_cert v);

    /**
     * @brief Downloads all attachments of the given message.
     * @param server Server URL.
     * @param path Path to output directory.
     * @param key API Key of Liquidfiles.
     * @param id Message id.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error, file_error.
     */
    void download(std::string server,
            const std::string& path,
            const std::string& key,
            const std::string& id,
            report_level s,
            validate_cert v);

    /**
     * @brief Downloads all attachments of the given messages.
     * @param server Server URL.
     * @param path Path to output directory.
     * @param key API Key of Liquidfiles.
     * @param l Hours, to get messages from the last specified hours.
     * @param f Date, to get messages from that date.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error, file_error.
     */
    void download(std::string server,
            const std::string& path,
            const std::string& key,
            const std::string& l,
            const std::string& f,
            report_level s,
            validate_cert v);

    /**
     * @brief Sends the file request to specified user, by specified server.
     * @param server Server URL.
     * @param user User name or email.
     * @param key API Key of Liquidfiles.
     * @param subject Subject of composed email.
     * @param message Message body of email.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error.
     */
    std::string file_request(std::string server,
            const std::string& user, 
            const std::string& key,
            const std::string& subject,
            const std::string& message,
            report_level s,
            validate_cert v);

    /**
     * @brief Gets the API key for the specified user.
     * @param server Server URL.
     * @param user User name or email.
     * @param password Password of the user.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error, get_api_key_error.
     */
    std::string get_api_key(std::string server,
            const std::string& user, 
            const std::string& password,
            report_level s,
            validate_cert v);

    /**
     * @brief Uploads current file and create filelink.
     * @param server Server URL.
     * @param key API Key of Liquidfiles.
     * @param file File path to upload.
     * @param s Silence flag.
     * @param v Validate certificate flag for HTTP request.
     * @throw curl_error.
     */
    std::string filelink(std::string server,
            const std::string& key,
            const std::string& expire,
            const std::string& file,
            report_level s,
            validate_cert v);
            
    /// @}

private:
    std::string attach(std::string server, const std::string& file,
            report_level s);

    std::string send_attachments(std::string server, const std::string& user,
            const std::string& subject, const std::string& message,
            const files& fs, report_level s);

    void init_curl(std::string key, report_level s, validate_cert v);

private:
    std::string process_send_responce(const std::string& r, report_level s) const;
    void process_attach_responce(const std::string& r, report_level s) const;
    void process_messages_responce(const std::string& r, report_level s, output_format f) const;
    void process_message_responce(const std::string& r, report_level s, output_format f) const;
    std::string message_impl(std::string server, const std::string& key, std::string id,
            report_level s, validate_cert v, std::string log);
    std::string messages_impl(std::string server, const std::string& key, std::string l,
            std::string f, report_level s, validate_cert v);
    std::string process_file_request_responce(const std::string& r, report_level s) const;
    std::string process_get_api_key_responce(const std::string& r, report_level s) const;
    std::string process_create_filelink_responce(const std::string& r, report_level s) const;

private:
    CURL* m_curl;
};

}
