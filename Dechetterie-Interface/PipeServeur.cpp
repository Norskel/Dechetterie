#include "stdafx.h"
#include "PipeServeur.h"

PipeServeur::~PipeServeur()
{
	_pipeInClientInterface->Close();
	_pipeOutClientInterface->Close();
}
