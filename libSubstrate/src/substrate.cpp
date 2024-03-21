#include <substrate/substrate.h>

#include <sstream>

#include <curl/curl.h>

std::string substrate::deps::get_curl_version_info()
{
   curl_version_info_data *version_info = curl_version_info(CURLVERSION_NOW);
   std::stringstream version_details;

   version_details << "cURL Version: " << version_info->version << "\n";
   version_details << "SSL Version: " << (version_info->ssl_version ? version_info->ssl_version : "Not Available") << "\n";
   version_details << "Libz Version: " << (version_info->libz_version ? version_info->libz_version : "Not Available") << "\n";
   version_details << "Protocols: ";

   for (const char *const *protocol = version_info->protocols; *protocol; ++protocol)
   {
      version_details << *protocol << " ";
   }

   return version_details.str();
}
