#pragma once
#include "../logger.h"
#include "../web/json_rpc_client.h"

#include <optional>
#include <type_traits>

// A helper trait to detect std::optional
template <typename T>
struct is_std_optional : std::false_type { };

template <typename T>
struct is_std_optional<std::optional<T>> : std::true_type { };

template <typename T>
inline constexpr bool is_std_optional_v = is_std_optional<T>::value;

// A helper trait to detect nlohmann::json
template <typename T>
struct is_json : std::false_type { };

template <>
struct is_json<nlohmann::json> : std::true_type { };

template <typename T>
inline constexpr bool is_json_v = is_json<T>::value;

namespace substrate::rpc::detail
{
   using namespace substrate::rpc;
   using namespace substrate::detail::web;

   class substrate_client final : public IClient
   {
      substrate::Logger _logger;

      std::string _url;
      json_rpc_client_ptr _socket;

      std::optional<RuntimeVersion> _runtimeVersion;
      std::optional<Hash> _genesisHash;

      constexpr static auto kCategory = "substrate_client";

   public:
      substrate_client(substrate::Logger logger, const std::string &url);
      virtual ~substrate_client() = default;

      [[nodiscard]] virtual bool connect() override;
      [[nodiscard]] virtual bool connected() const override;

      virtual void wait() override;

      [[nodiscard]] virtual RuntimeVersion getRuntimeVersion() const override;
      virtual void setRuntimeVersion(RuntimeVersion version) override;

      [[nodiscard]] virtual Hash getGenesisHash() const override;
      virtual void setGenesisHash(Hash hash) override;

      [[nodiscard]] Extrinsic make_extrinsic(
          substrate::Account account,
          Method call,
          ChargeType charge = ChargeType(),
          uint32_t lifeTime = 0) const override;

      SUBSTRATE_IMPL_RPC_CLIENT

   private:
      template <typename T>
      void add_to_json(nlohmann::json &json, T &&value) const
      {
         if constexpr (is_std_optional_v<std::decay_t<T>>)
         {
            if (value.has_value())
            {
               json.push_back(nlohmann::json(*value));
            }
         }
         else
         {
            json.push_back(nlohmann::json(value));
         }
      }

      template <typename... Args>
      nlohmann::json json_encode_params(Args &&...args) const
      {
         auto result = nlohmann::json::array();
         (add_to_json(result, std::forward<Args>(args)), ...);
         return result;
      }

      template <typename TReturn, typename... Args>
      TReturn rpc(const std::string &name, Args &&...args) const
      {
         const auto params = json_encode_params(std::forward<Args>(args)...);
         const auto result = _socket->send_rpc_result(name, params);

         if constexpr (is_std_optional_v<std::decay_t<TReturn>>)
         {
            if (result.is_null() || result.empty())
               return std::nullopt;


            // TODO: Get actual type of TReturn and parse it.
            return std::nullopt;
         }
         else
         {
            if constexpr (is_json_v<TReturn>)
            {
               return result;
            }
            else
            {
               TReturn ret;
               from_json(result, ret);
               return ret;
            }
         }
      }

      template <typename TReturn, typename... Args>
      TReturn rpc(const std::string &name) const
      {
         const auto result = _socket->send_rpc_result(name);
         if constexpr (is_json_v<TReturn>)
         {
            return result;
         }
         else
         {
            TReturn ret;
            from_json(result, ret);
            return ret;
         }
      }
   };
}