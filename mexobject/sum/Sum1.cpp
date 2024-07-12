#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nlhs>1)
		mexErrMsgIdAndTxt("MATLAB:f1_mex:invalidNumOutputs", "One output required.");
	if (nrhs != 2)
		mexErrMsgIdAndTxt("MATLAB:f1_mex:invalidNumInputs", "One input required.");

	size_t row1 = mxGetM(prhs[0]);
	size_t row2 = mxGetM(prhs[1]);
	size_t col1 = mxGetN(prhs[0]);
	size_t col2 = mxGetN(prhs[1]);

	if (row1 != row2 && col1 != col2)
		mexErrMsgIdAndTxt("MATLAB:f1_mex:invalidNumInputs", "input error.");

	double *p1 = mxGetPr(prhs[0]);
	double *p2 = mxGetPr(prhs[1]);

	plhs[0] = mxCreateDoubleMatrix(row1, col1, mxREAL);
	double *f = mxGetPr(plhs[0]);

	for (int i = 0; i < row1*col1; ++i)
		f[i] = p1[i] + p2[i];
}