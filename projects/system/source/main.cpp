#include <iostream>

#include "../../shared/source/logger/logger.hpp"

#include "system/system.hpp"

using Logger = solution::shared::Logger;

int main(int argc, char** argv)
{
	RUN_LOGGER(logger);

	try
	{
		solution::system::System().run();

		system("pause");

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		logger.write(Logger::Severity::fatal, exception.what());

		return EXIT_FAILURE;
	}
	catch (...)
	{
		logger.write(Logger::Severity::fatal, "unknown exception");

		return EXIT_FAILURE;
	}
}