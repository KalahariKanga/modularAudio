#include "Filter.h"


Filter::Filter()
{
	type.create(1, 0, 1);
	freq.create(440, 20, SAMPLE_RATE / 20);
	q.create(0.6, 0.001, 1);
	parameters.insert(std::pair<std::string, Parameter*>("type", &type));
	parameters.insert(std::pair<std::string, Parameter*>("freq", &freq));
	parameters.insert(std::pair<std::string, Parameter*>("q", &q));
	zx[0] = 0;
	zx[1] = 0;
	zy[0] = 0;
	zy[1] = 0;
}


Filter::~Filter()
{
}

float Filter::processSample(float in)
{
	float out;
	out = a0*in + a1*zx[0] + a2*zx[1] - b1*zy[0] - b2*zy[1];
	zx[1] = zx[0];
	zx[0] = in;
	zy[1] = zy[0];
	zy[0] = out;
	return out;
}

void Filter::calcCoeffs()
{
	float normf = freq.getValue() / SAMPLE_RATE;
	float theta = 2 * PI * normf;
	float d = 0.5 * (1 / q.getValue()) * sin(theta);
	float beta = 0.5 * ((1 - d) / (1 + d));
	float gamma = (0.5 + beta) * cos(theta);


	if (type.getValue() == 0) {
		a0 = 0.5 * (0.5 + beta - gamma);
		a1 = 0.5 + beta - gamma;
	}
	else {
		a0 = 0.5 * (0.5 + beta + gamma);
		a1 = -(0.5 + beta + gamma);
	}
	a2 = a0;
	b1 = -2. * gamma;
	b2 = 2. * beta;

}

void Filter::render()
{
	calcCoeffs();
	buffer.zero();
	for (auto i : ins)
	{
		for (int c = 0; c < BUFFER_LENGTH; c++)
			buffer[c] += i->buffer[c];
	}
	for (int c = 0; c < BUFFER_LENGTH; c++)
		buffer[c] = processSample(buffer[c]);
}