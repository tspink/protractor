/**
 * src/client.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <client.h>

using namespace protractor;

ProtractorClient::ProtractorClient(fd::FileDescriptor* transport) : _transport(transport)
{

}
