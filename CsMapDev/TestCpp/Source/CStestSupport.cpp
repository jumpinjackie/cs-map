/*
 * Copyright (c) 2008, Autodesk, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autodesk, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Autodesk, Inc. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Autodesk, Inc. OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "cs_map.h"
#include "csTestCpp.hpp"

extern "C"
{
	extern int cs_Error;
	extern int cs_Errno;
	extern int csErrlng;
	extern int csErrlat;
	extern unsigned short cs_ErrSup;
	#if _RUN_TIME <= _rt_UNIXPCC
	extern ulong32_t cs_Doserr;
	#endif

	extern char cs_OptchrC;

	extern double cs_Zero;
	extern double cs_One;
	extern double cs_Mone;
	extern double cs_Degree;
	extern double cs_MaxLatFz;
	extern double cs_Km360;
	extern double cs_Radian;

	extern char cs_Dir [];
	extern char *cs_DirP;

	extern struct csNad27ToNad83_* csNad27ToNad83;
	extern struct csNad83ToHarn_* csNad83ToHarn;
	extern struct csAgd66ToGda94_* csAgd66ToGda94;
	extern struct csAgd84ToGda94_* csAgd84ToGda94;
	extern struct csNzgd49ToNzgd2K_* csNzgd49ToNzgd2K;

	extern struct csAts77ToCsrs_* csAts77ToCsrs;
	extern struct csNad83ToCsrs_* csNad83ToCsrs;
	extern struct csVertconUS_* csVertconUS;
	extern struct cs_Osgm91_ *cs_Osgm91Ptr;
	extern struct csTokyoToJgd2k_ *csTokyoToJgd2k;
	extern struct csRgf93ToNtf_* csRgf93ToNtf;
	extern struct csEd50ToEtrf89_* csEd50ToEtrf89;
	extern struct csDhdnToEtrf89_* csDhdnToEtrf89;

	extern struct cs_Ostn97_ *cs_Ostn97Ptr;
	extern struct cs_Ostn02_ *cs_Ostn02Ptr;
}

void CS_reset ()
{
	CS_recvr ();
	CSdeleteNad27ToNad83 (csNad27ToNad83);
	csNad27ToNad83 = NULL;
	CSdeleteNad83ToHarn (csNad83ToHarn);
	csNad83ToHarn = NULL;
	CSdeleteAgd66ToGda94 (csAgd66ToGda94);
	csAgd66ToGda94 = NULL;
	CSdeleteAgd84ToGda94 (csAgd84ToGda94);
	csAgd84ToGda94 = NULL;
	CSdeleteNzgd49ToNzgd2K (csNzgd49ToNzgd2K);
	csNzgd49ToNzgd2K = NULL;
	CSdeleteAts77ToCsrs (csAts77ToCsrs);
	csAts77ToCsrs = NULL;
	CSdeleteNad83ToCsrs (csNad83ToCsrs);
	csNad83ToCsrs = NULL;
	CSdeleteVertconUS (csVertconUS);
	csVertconUS = NULL;
	CSdeleteOsgm91 (cs_Osgm91Ptr);
	cs_Osgm91Ptr = NULL;
	CSdeleteTokyoToJgd2k (csTokyoToJgd2k);
	csTokyoToJgd2k = NULL;
	CSdeleteRgf93ToNtf (csRgf93ToNtf);
	csRgf93ToNtf = NULL;
	CSdeleteOstn97 (cs_Ostn97Ptr);
	cs_Ostn97Ptr = NULL;
	CSdeleteOstn02 (cs_Ostn02Ptr);
	cs_Ostn02Ptr = NULL;
	CSdeleteEd50ToEtrf89 (csEd50ToEtrf89);
	csEd50ToEtrf89 = NULL;
	CSdeleteDhdnToEtrf89 (csDhdnToEtrf89);
	csDhdnToEtrf89 = NULL;
    csReleaseNameMapper ();

	CS_stcpy (cs_DirP,"Japan\\TKY2JGD._jg");
	CS_remove (cs_Dir);
	CS_stcpy (cs_DirP,"OSTN02._02");
	CS_remove (cs_Dir);
	CS_stcpy (cs_DirP,"OSTN97._nt");
	CS_remove (cs_Dir);
	CS_stcpy (cs_DirP,"OSGM91._gm");
	CS_remove (cs_Dir);
}

double CStestRN (double low, double high)
{
	unsigned irand;

	double rrand;

	irand = rand ();
	rrand = low + (high - low) * ((double)irand / (double)RAND_MAX);
	return (rrand);
}

int CStestXYZ (double xyz [3],double falseOrg [2],unsigned* sequencer)
{
	extern double cs_Zero;

	int done;

	unsigned seq;
	unsigned irandX;
	unsigned irandY;
	unsigned irandZ;

	double rrandX;
	double rrandY;
	double rrandZ;
	double factor;

	done = 0;
	seq = *sequencer;
	*sequencer += 1;
	if (*sequencer >= 0x1FF)
	{
		*sequencer = 1;
		done = 1;
	}

	irandX = rand ();
	irandY = rand ();
	irandZ = rand ();

	if (seq == 0)
	{
		rrandX = rrandY = rrandZ = cs_Zero;
	}
	else
	{
		rrandX = ((double)irandX / (double)RAND_MAX);
		rrandY = ((double)irandY / (double)RAND_MAX);
		rrandZ = ((double)irandZ / (double)RAND_MAX);
		factor = rrandX * rrandY * rrandZ;
		if (fabs (factor) < 1.0E-06)
		{
			factor = 1.234567E+06;
		}

		if ((seq & 0x7) != 7)
		{
			if ((seq & 0x01) != 0) rrandX = cs_Zero;
			if ((seq & 0x02) != 2) rrandY = cs_Zero;
			if ((seq & 0x04) != 0) rrandZ = cs_Zero;
		}
		seq >>= 3;

		if ((seq & 0x1) != 0) rrandX = -rrandX;
		if ((seq & 0x2) != 0) rrandY = -rrandY;
		if ((seq & 0x4) != 0) rrandZ = -rrandZ;
		seq >>= 3;
		
		rrandX += falseOrg [0];
		rrandY += falseOrg [1];

		switch (seq % 7) {
		case 1:
			rrandX *= factor;
			rrandY *= factor;
			break;			
		case 2:
			rrandX /= factor;
			rrandY *= factor;
			break;			
		case 3:
			rrandX *= factor;
			rrandY /= factor;
			break;			
		case 4:
			rrandX /= factor;
			rrandY /= factor;
			break;			
		case 5:
			rrandZ *= factor;
			break;			
		case 6:
			rrandZ /= factor;
			break;			
		case 7:
			rrandX *= factor;
			rrandY *= factor;
			rrandZ *= factor;
			break;			
		case 0:
		default:
			break;
		}
	}

	xyz [0] = rrandX;
	xyz [1] = rrandY;
	xyz [2] = rrandZ;
	return done;
}

int CStestLLH (double llh [2],double cntrlMer,unsigned* sequencer)
{
	int done;

	unsigned seq;
	unsigned irandLng;
	unsigned irandLat;
	unsigned irandHgt;

	double rrandLng;
	double rrandLat;
	double rrandHgt;
	double factor;

	done = 0;
	seq = *sequencer;
	*sequencer += 1;
	if (*sequencer >= 0x3FF)
	{
		*sequencer = 1;
		done = 1;
	}

	irandLng = rand ();
	irandLat = rand ();
	irandHgt = rand ();

	if (seq == 0)
	{
		rrandLng = rrandLat = rrandHgt = cs_Zero;
	}
	else if ((seq & 0x200) == 0)
	{
		rrandLng = ((double)irandLng / (double)RAND_MAX) *  180.0;
		rrandLat = ((double)irandLat / (double)RAND_MAX) *   90.0;
		rrandHgt = ((double)irandHgt / (double)RAND_MAX) * 5000.0;
		factor = rrandLng * rrandLat * rrandHgt;
		if (fabs (factor) < 1.0E-06)
		{
			factor = 12.345678E+06;
		}

		if ((seq & 0x7) != 7)
		{
			if ((seq & 0x01) != 0) rrandLng = cs_Zero;
			if ((seq & 0x02) != 2) rrandLat = cs_Zero;
			if ((seq & 0x04) != 0) rrandHgt = cs_Zero;
		}
		seq >>= 3;

		if ((seq & 0x1) != 0) rrandLng = -rrandLng;
		if ((seq & 0x2) != 0) rrandLat = -rrandLat;
		if ((seq & 0x4) != 0) rrandHgt = -rrandHgt;
		seq >>= 3;

		switch (seq % 7) {
		case 1:
			rrandLng *= factor;
			rrandLat *= factor;
			break;			
		case 2:
			rrandLng /= factor;
			rrandLat *= factor;
			break;			
		case 3:
			rrandLng *= factor;
			rrandLat /= factor;
			break;			
		case 4:
			rrandLng /= factor;
			rrandLat /= factor;
			break;			
		case 5:
			rrandHgt *= factor;
			break;			
		case 6:
			rrandHgt /= factor;
			break;			
		case 7:
			rrandLng *= factor;
			rrandLat *= factor;
			rrandHgt *= factor;
			break;			
		case 0:
		default:
			break;
		}
	}
	else
	{
		rrandLng = cntrlMer + (double)(((int)irandLng % 180) - 90);
		rrandLat = (double)(((int)irandLat % 180) - 90);
		rrandHgt = (double)(((int)irandHgt % 5000) - 2500);
	}

	llh [0] = rrandLng;
	llh [1] = rrandLat;
	llh [2] = rrandHgt;

	return done;
}

/*
	The following function calculates the K scale factor, i.e.
	grid scale along a parallels. For the algorithm in use, see
	Synder/Bugayevskiy, page 18. They call it "n".
*/
double CStstsclk (struct cs_Csprm_ *csprm,double ll [2])
{
	int status;

	double N;
	double kk;
	double lat;
	double tmp;
	double delta;
	double cos_lat;
	double del_xx;
	double del_yy;
	double e_rad;
	double ecent;

	double xy1 [3];
	double xy2 [3];
	double my_ll [3];

	/* K is not defined at the poles. */

	if (fabs (ll [LAT]) >= cs_MaxLatFz)
	{
		return (cs_Mone);
	}

	my_ll [LNG] = ll [LNG];
	my_ll [LAT] = ll [LAT];

	lat = my_ll [LAT] * cs_Degree;
	cos_lat = cos (lat);

	/* Since the actual magnitude of longitude varies with
	   latitude, we adjust the "infinitesimal" delta which
	   we use to simulate the partial deriviative by the
	   cosine of the latitude. */

	delta = 0.00005 / cos_lat;

	my_ll [LNG] -= delta;
	status = CS_ll2cs (csprm,xy1,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Mone);
	}
	my_ll [LNG] += (delta + delta);
	status = CS_ll2cs (csprm,xy2,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Mone);
	}
	del_xx = (xy2 [XX] - xy1 [XX]);
	del_yy = (xy2 [YY] - xy1 [YY]);

	/* e_rad is the equatorial radius in system units. */

	e_rad = csprm->datum.e_rad * csprm->csdef.scale;
	ecent = csprm->datum.ecent;

	if (ecent == 0.0 || (csprm->prj_flags & cs_PRJFLG_ELLIPS) == 0)
	{
		/* Here if the reference ellipsoid is actually a
		   sphere, or the projection is defined for the
		   sphere only. */

		N = e_rad;
	}
	else
	{
		/* Need to take the ellipsoid into account. */

		tmp = ecent * sin (lat);
		N = e_rad / sqrt (cs_One - tmp * tmp);
	}
	N *= 2.0 * delta * cs_Degree;

	kk = sqrt (del_xx * del_xx + del_yy * del_yy) / (N * cos_lat);
	return (kk);
}

/*
	The following function calculates the H scale factor, i.e.
	grid scale along a meridian.  See Synder/Bugayevskiy, page 17.
	They call it "m".
*/
double CStstsclh (struct cs_Csprm_ *csprm,double ll [2])
{
	int status;

	double M;
	double hh;
	double lat;
	double tmp;
	double del_xx;
	double del_yy;
	double e_rad;
	double ecent;

	double xy1 [3];
	double xy2 [3];
	double my_ll [3];

	my_ll [LNG] = ll [LNG];
	my_ll [LAT] = ll [LAT];

	lat = my_ll [LAT] * cs_Degree;

	my_ll [LAT] -= 0.0001;
	status = CS_ll2cs (csprm,xy1,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Mone);
	}
	my_ll [LAT] += 0.0001;
	status = CS_ll2cs (csprm,xy2,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Mone);
	}
	del_xx = (xy2 [XX] - xy1 [XX]);
	del_yy = (xy2 [YY] - xy1 [YY]);

	/* e_rad is the equatorial radius in system units. */

	e_rad = csprm->datum.e_rad * csprm->csdef.scale;
	ecent = csprm->datum.ecent;

	if (ecent == 0.0 || ((csprm->prj_flags & cs_PRJFLG_ELLIPS) == 0))
	{
		/* Here if the reference ellipsoid is actually a
		   sphere, or the projection is defined for the
		   sphere only. */

		M = e_rad;
	}
	else
	{
		/* Need to take the ellipsoid into account. */
		tmp = ecent * sin (lat);
		tmp = cs_One - tmp * tmp;
		M = e_rad * (cs_One - (ecent * ecent)) / (tmp * sqrt (tmp));
	}
	M *= 0.0001 * cs_Degree;

	hh = sqrt (del_xx * del_xx + del_yy * del_yy) / M;
	return (hh);
}

double CStstcnvrg (struct cs_Csprm_ *csprm,double ll [2])
{
	int status;

	double del_xx;
	double del_yy;
	double gamma;

	double xy1 [3];
	double xy2 [3];
	double my_ll [3];

	my_ll [LNG] = ll [LNG];
	my_ll [LAT] = ll [LAT];

	my_ll [LAT] -= 0.00005;
	status = CS_ll2cs (csprm,xy1,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Km360);
	}
	ll [LAT] += 0.0001;
	status = CS_ll2cs (csprm,xy2,my_ll);
	if (status != cs_CNVRT_NRML)
	{
		return (cs_Km360);
	}

	del_xx = xy2 [0] - xy1 [0];
	del_yy = xy2 [1] - xy1 [1];
	if ((fabs (del_xx) + fabs (del_yy)) > 0.0)
	{
		gamma = -atan2 (del_xx,del_yy) * cs_Radian;
	}
	else
	{
		gamma = cs_Km360;
	}
	return (gamma);
}

void usage (bool batch)
{
	printf ("Usage: TEST [%cb] [%cv] [%cp30] [%cddir] [%ct123] [test_file]\n",
		cs_OptchrC,cs_OptchrC,cs_OptchrC,cs_OptchrC,cs_OptchrC);
	printf ("\t       %cb  supresses acknowledgement before exit\n",cs_OptchrC);
	printf ("\t       %cd  specifies Dictionary directory\n",cs_OptchrC);
	printf ("\t       %cl  test environement locale name\n",cs_OptchrC);
	printf ("\t       %cp  test duration parameter\n",cs_OptchrC);
	printf ("\t       %cr  specify random number seed value\n",cs_OptchrC);
	printf ("\t       %cs  indicates binary data files are swapped\n",cs_OptchrC);
	printf ("\t       %ct  specifies tests, and sequence\n",cs_OptchrC);
	printf ("\t       %cv  start in verbose mode\n",cs_OptchrC);
	printf ("\ttest_file  name of test data file\n\n");
	if (!batch)
	{
		printf ("Press any key to continue: ");
		fflush (stdout);
		getchar ();
		printf ("\n");
	}
	exit (1);
}
