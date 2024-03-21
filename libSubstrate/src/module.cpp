#include "module.h"

substrate::detail::module::module(substrate::Logger logger, web::json_rpc_client_ptr socket)
    : _logger(logger), _socket(socket)
{
}
