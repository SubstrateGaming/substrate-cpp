#pragma once

#ifndef SLOG_DEBUG
#define SLOG_DEBUG(category, message) _logger ? _logger->debug(category, message) : (void)_logger;
#endif

#ifndef SLOG_INFO
#define SLOG_INFO(category, message) _logger ? _logger->info(category, message) : (void)_logger;
#endif

#ifndef SLOG_WARN
#define SLOG_WARN(category, message) _logger ? _logger->warn(category, message) : (void)_logger;
#endif

#ifndef SLOG_ERROR
#define SLOG_ERROR(category, message) _logger ? _logger->error(category, message) : (void)_logger;
#endif
