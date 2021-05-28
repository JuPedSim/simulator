import logging

logger = logging.getLogger("JuPedSim")


def log_debug(msg, **kwargs):
    logger.debug(msg, **kwargs)


def log_info(msg, **kwargs):
    logger.info(msg, **kwargs)


def log_warning(msg, **kwargs):
    logger.warning(msg, **kwargs)


def log_error(msg, **kwargs):
    logger.error(msg, **kwargs)


native_logger = logging.getLogger("libcore")


def log_native_debug(msg, **kwargs):
    native_logger.debug(msg, **kwargs)


def log_native_info(msg, **kwargs):
    native_logger.info(msg, **kwargs)


def log_native_warning(msg, **kwargs):
    native_logger.warning(msg, **kwargs)


def log_native_error(msg, **kwargs):
    native_logger.error(msg, **kwargs)
