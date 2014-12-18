#include "header.h"
#include "ImageTriangle.h"
#include "triangle/triangle.h"
void ImageTriangle::bulitTri(vector<REAL> &pointX,vector<REAL> &pointY,struct triangulateio &mid)
{
	struct triangulateio in,out, vorout;

	/* Define input points. */

	in.numberofpoints = pointX.size();
	in.numberofpointattributes = 1;
	initTriangulateio(in);
	initTriangulateio(out);
	initTriangulateio(vorout);
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	for(int i=0;i<in.numberofpoints;++i)
	{
		in.pointlist[2*i]=pointX[i];
		in.pointlist[2*i+1]=pointY[i];
	}
	in.pointattributelist = (REAL *) malloc(in.numberofpoints *
		in.numberofpointattributes *
		sizeof(REAL));
	in.pointattributelist[0] = 0.0;
	in.pointattributelist[1] = 1.0;
	in.pointattributelist[2] = 11.0;
	in.pointattributelist[3] = 10.0;
	in.pointmarkerlist = (int *) malloc(in.numberofpoints * sizeof(int));
	in.pointmarkerlist[0] = 0;
	in.pointmarkerlist[1] = 2;
	in.pointmarkerlist[2] = 0;
	in.pointmarkerlist[3] = 0;

	in.numberofsegments = 0;
	in.numberofholes = 0;
	in.numberofregions = 1;
	in.regionlist = (REAL *) malloc(in.numberofregions * 4 * sizeof(REAL));
	in.regionlist[0] = 0.5;
	in.regionlist[1] = 5.0;
	in.regionlist[2] = 7.0;            /* Regional attribute (for whole mesh). */
	in.regionlist[3] = 0.1;          /* Area constraint that will not be used. */

	/* Make necessary initializations so that Triangle can return a */
	/*   triangulation in `mid' and a voronoi diagram in `vorout'.  */

	//mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
	////* Not needed if -N switch used or number of point attributes is zero: */
	//mid.pointattributelist = (REAL *) NULL;
	//mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
	//mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
	////* Not needed if -E switch used or number of triangle attributes is zero: */
	//mid.triangleattributelist = (REAL *) NULL;
	//mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	////* Needed only if segments are output (-p or -c) and -P not used: */
	//mid.segmentlist = (int *) NULL;
	////* Needed only if segments are output (-p or -c) and -P and -B not used: */
	//mid.segmentmarkerlist = (int *) NULL;
	//mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	//mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */

	//vorout.pointlist = (REAL *) NULL;        /* Needed only if -v switch used. */
	////* Needed only if -v switch used and number of attributes is not zero: */
	//vorout.pointattributelist = (REAL *) NULL;
	//vorout.edgelist = (int *) NULL;          /* Needed only if -v switch used. */
	//vorout.normlist = (REAL *) NULL;         /* Needed only if -v switch used. */

	/* Triangulate the points.  Switches are chosen to read and write a  */
	/*   PSLG (p), preserve the convex hull (c), number everything from  */
	/*   zero (z), assign a regional attribute to each element (A), and  */
	/*   produce an edge list (e), a Voronoi diagram (v), and a triangle */
	/*   neighbor list (n).                                              */
	triangulate("pczAevn", &in, &mid, &vorout);
	freeTriangulateio(in);
	freeTriangulateio(vorout);
}
void ImageTriangle::initTriangulateio(struct triangulateio &io)
{
	io.edgelist=NULL;
	io.edgemarkerlist=NULL;
	io.holelist=NULL;
	io.neighborlist=NULL;
	io.normlist=NULL;
	io.pointattributelist=NULL;
	io.pointmarkerlist=NULL;
	io.pointlist=NULL;
	io.regionlist=NULL;
	io.segmentlist=NULL;
	io.segmentmarkerlist=NULL;
	io.trianglearealist=NULL;
	io.triangleattributelist=NULL;
	io.trianglelist=NULL;
	//io.numberofcorners=0;
	//io.numberofedges=0;
	//io.numberofholes=0;
	//io.numberofpointattributes=0;
	//io.numberofpoints=0;
	//io.numberofregions=0;
	//io.numberofsegments=0;
	//io.numberoftriangleattributes=0;
	//io.numberoftriangles=0;
}
void ImageTriangle::freeTriangulateio(struct triangulateio &io)
{
	free(io.edgelist);
	free(io.edgemarkerlist);
	free(io.holelist);
	free(io.neighborlist);
	free(io.normlist);
	free(io.pointattributelist);
	free(io.pointlist);
	free(io.pointmarkerlist);
	free(io.regionlist);
	free(io.segmentlist);
	free(io.segmentmarkerlist);
	free(io.trianglearealist);
	free(io.triangleattributelist);
	free(io.trianglelist);
	initTriangulateio(io);
}