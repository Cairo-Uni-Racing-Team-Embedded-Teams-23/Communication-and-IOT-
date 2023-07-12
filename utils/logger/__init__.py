import logging


def setup_logger(log_file=None, log_level=logging.DEBUG):
    """
    Initializes a logger instance with the given log file and log level.

    Parameters:
        log_file (str): The path to the log file. Defaults to None.
        log_level (int): The log level. Defaults to logging.DEBUG.

    Returns:
        logging.Logger: The logger instance.
    """
    # Create a logger instance if it doesn't exist
    logger = logging.getLogger(__name__)
    if not logger.handlers:
        # Set the log level
        logger.setLevel(log_level)

        # Create a console handler to log to the console
        console_handler = logging.StreamHandler()
        console_handler.setLevel(log_level)
        # Create a formatter for the console handler
        console_formatter = logging.Formatter(
            "%(asctime)s - %(name)s - %(levelname)s - %(message)s"
        )
        console_handler.setFormatter(console_formatter)
        logger.addHandler(console_handler)

        # Create a file handler if log_file is provided
        if log_file:
            file_handler = logging.FileHandler(log_file)
            file_handler.setLevel(log_level)
            # Create a formatter for the file handler
            file_formatter = logging.Formatter(
                "%(asctime)s - %(name)s - %(levelname)s - %(message)s"
            )
            file_handler.setFormatter(file_formatter)
            logger.addHandler(file_handler)

    return logger
