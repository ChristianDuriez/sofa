/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 4      *
*                (c) 2006-2009 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                              SOFA :: Framework                              *
*                                                                             *
* Authors: M. Adam, J. Allard, B. Andre, P-J. Bensoussan, S. Cotin, C. Duriez,*
* H. Delingette, F. Falipou, F. Faure, S. Fonteneau, L. Heigeas, C. Mendoza,  *
* M. Nesme, P. Neumann, J-P. de la Plata Alcade, F. Poyer and F. Roy          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_CORE_TOPOLOGY_BASEMESHTOPOLOGY_H
#define SOFA_CORE_TOPOLOGY_BASEMESHTOPOLOGY_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sofa/core/topology/Topology.h>
#include <sofa/core/objectmodel/DataFileName.h>
#include <sofa/helper/fixed_array.h>
#include <sofa/helper/vector.h>
#include <sofa/helper/list.h>

#include <sofa/core/core.h>

namespace sofa
{

namespace core
{

namespace topology
{

using namespace sofa::defaulttype;
using helper::vector;
using helper::fixed_array;

#define SOFA_NEW_HEXA

class SOFA_CORE_API BaseMeshTopology : public core::topology::Topology
{
public:
    SOFA_CLASS(BaseMeshTopology, core::topology::Topology);
    //typedef int index_type;
    typedef unsigned int index_type;
    enum { InvalidID = (unsigned)-1 };
    typedef index_type	        	        PointID;
    typedef index_type          		EdgeID;
    typedef index_type           		TriangleID;
    typedef index_type                 		QuadID;
    typedef index_type	                	TetraID;
    typedef index_type	                	HexaID;

    typedef fixed_array<PointID,2>              Edge;
    typedef fixed_array<PointID,3>              Triangle;
    typedef fixed_array<PointID,4>              Quad;
    typedef fixed_array<PointID,4>              Tetra;
    typedef fixed_array<PointID,8>              Hexa;

    typedef vector<Edge> 		        SeqEdges;
    typedef vector<Triangle>		        SeqTriangles;
    typedef vector<Quad>		        SeqQuads;
    typedef vector<Tetra>		        SeqTetrahedra;
    typedef vector<Hexa>		        SeqHexahedra;

    /// @name Deprecated types, for backward-compatibility
    /// @{
    typedef EdgeID		                LineID;
    typedef Edge		                Line;
    typedef SeqEdges	                        SeqLines;
#ifndef SOFA_NEW_HEXA
    typedef HexaID                              CubeID;
    typedef Hexa                                Cube;
    typedef SeqHexahedra                        SeqCubes;
#endif
    /// @}

    /// fixed-size neighbors arrays
    /// @{
    typedef fixed_array<EdgeID,3>		EdgesInTriangle;
    typedef fixed_array<EdgeID,4>		EdgesInQuad;
    typedef fixed_array<TriangleID,4>	TrianglesInTetrahedron;
    typedef fixed_array<EdgeID,6>		EdgesInTetrahedron;
    typedef fixed_array<QuadID,6>		QuadsInHexahedron;
    typedef fixed_array<EdgeID,12>		EdgesInHexahedron;
    /// @}

    /// dynamic-size neighbors arrays
    /// @{
    typedef vector<PointID>		VerticesAroundVertex;
    typedef vector<EdgeID>			EdgesAroundVertex;
    typedef vector<TriangleID>	TrianglesAroundVertex;
    typedef vector<QuadID>			QuadsAroundVertex;
    typedef vector<TetraID>		TetrahedraAroundVertex;
    typedef vector<HexaID>			HexahedraAroundVertex;
    typedef vector<TriangleID>	TrianglesAroundEdge;
    typedef vector<QuadID>			QuadsAroundEdge;
    typedef vector<TetraID>		TetrahedraAroundEdge;
    typedef vector<HexaID>			HexahedraAroundEdge;
    typedef vector<TetraID>		TetrahedraAroundTriangle;
    typedef vector<HexaID>			HexahedraAroundQuad;
    /// @}

    BaseMeshTopology()	;
    virtual void init();

    /// Load the topology from a file.
    ///
    /// The default implementation supports the following formats: obj, gmsh, mesh (custom simple text file), xs3 (deprecated description of mass-springs networks).
    virtual bool load(const char* filename);
    virtual std::string getFilename() const {return fileTopology.getValue();}

    // defined in Topology
    //virtual int getNbPoints() const = 0;

    /// Complete sequence accessors
    /// @{
    virtual const SeqEdges& getEdges() = 0;
    virtual const SeqTriangles& getTriangles() = 0;
    virtual const SeqQuads& getQuads() = 0;
    virtual const SeqTetrahedra& getTetrahedra() = 0;
    virtual const SeqHexahedra& getHexahedra() = 0;
    /// @}

    /// Random accessors
    /// @{

    virtual int getNbEdges()                   { return getEdges().size(); }
    virtual int getNbTriangles()               { return getTriangles().size(); }
    virtual int getNbQuads()                   { return getQuads().size(); }
    virtual int getNbTetrahedra()              { return getTetrahedra().size(); }
    virtual int getNbHexahedra()	       { return getHexahedra().size(); }

    virtual const Edge getEdge(EdgeID i)             { return getEdges()[i]; }
    virtual const Triangle getTriangle(TriangleID i) { return getTriangles()[i]; }
    virtual const Quad getQuad(QuadID i)             { return getQuads()[i]; }
    virtual const Tetra getTetrahedron(TetraID i)    { return getTetrahedra()[i]; }
    virtual const Hexa getHexahedron(HexaID i)       { return getHexahedra()[i]; }
    /// @}

    /// Bridge from old functions (using Tetra/Tetras and Hexa/Hexas) to new ones
    ///@{
    virtual int getNbTetras()    { return getTetrahedra().size(); }
    virtual int getNbHexas()     { return getHexahedra().size(); }

    virtual Tetra getTetra(TetraID i)          { return getTetrahedra()[i]; }
    virtual Hexa getHexa(HexaID i)             { return getHexahedra()[i]; }

    virtual const SeqTetrahedra& getTetras() {return getTetrahedra();}
    virtual const SeqHexahedra& getHexas() {return getHexahedra();}
    /// @}

    /// @name neighbors queries
    /// @{
    /// Returns the set of edges adjacent to a given vertex.
    virtual const EdgesAroundVertex& getEdgesAroundVertex(PointID i);
    /// Returns the set of edges adjacent to a given triangle.
    virtual const EdgesInTriangle& getEdgesInTriangle(TriangleID i);
    /// Returns the set of edges adjacent to a given quad.
    virtual const EdgesInQuad& getEdgesInQuad(QuadID i);
    /// Returns the set of edges adjacent to a given tetrahedron.
    virtual const EdgesInTetrahedron& getEdgesInTetrahedron(TetraID i);
    /// Returns the set of edges adjacent to a given hexahedron.
    virtual const EdgesInHexahedron& getEdgesInHexahedron(HexaID i);
    /// Returns the set of triangles adjacent to a given vertex.
    virtual const TrianglesAroundVertex& getTrianglesAroundVertex(PointID i);
    /// Returns the set of triangles adjacent to a given edge.
    virtual const TrianglesAroundEdge& getTrianglesAroundEdge(EdgeID i);
    /// Returns the set of triangles adjacent to a given tetrahedron.
    virtual const TrianglesInTetrahedron& getTrianglesInTetrahedron(TetraID i);
    /// Returns the set of quads adjacent to a given vertex.
    virtual const QuadsAroundVertex& getQuadsAroundVertex(PointID i);
    /// Returns the set of quads adjacent to a given edge.
    virtual const QuadsAroundEdge& getQuadsAroundEdge(EdgeID i);
    /// Returns the set of quads adjacent to a given hexahedron.
    virtual const QuadsInHexahedron& getQuadsInHexahedron(HexaID i);
    /// Returns the set of tetrahedra adjacent to a given vertex.
    virtual const TetrahedraAroundVertex& getTetrahedraAroundVertex(PointID i);
    /// Returns the set of tetrahedra adjacent to a given edge.
    virtual const TetrahedraAroundEdge& getTetrahedraAroundEdge(EdgeID i);
    /// Returns the set of tetrahedra adjacent to a given triangle.
    virtual const TetrahedraAroundTriangle& getTetrahedraAroundTriangle(TriangleID i);
    /// Returns the set of hexahedra adjacent to a given vertex.
    virtual const HexahedraAroundVertex& getHexahedraAroundVertex(PointID i);
    /// Returns the set of hexahedra adjacent to a given edge.
    virtual const HexahedraAroundEdge& getHexahedraAroundEdge(EdgeID i);
    /// Returns the set of hexahedra adjacent to a given quad.
    virtual const HexahedraAroundQuad& getHexahedraAroundQuad(QuadID i);

    /// Returns the set of vertices adjacent to a given vertex (i.e. sharing an edge)
    virtual const VerticesAroundVertex getVerticesAroundVertex(PointID i);
    /// Returns the set of element indices adjacent to a given element (i.e. sharing a link)
    virtual const vector<index_type> getElementAroundElement(index_type elem);
    /// Returns the set of element indices adjacent to a given list of elements (i.e. sharing a link)
    virtual const vector<index_type> getElementAroundElements(vector<index_type> elems);
    /// @}


    /// Returns the index of the edge joining vertex v1 and vertex v2; returns -1 if no edge exists
    virtual int getEdgeIndex(PointID v1, PointID v2);
    /// Returns the index of the triangle given three vertex indices; returns -1 if no triangle exists
    virtual int getTriangleIndex(PointID v1, PointID v2, PointID v3);
    /// Returns the index of the quad given four vertex indices; returns -1 if no quad exists
    virtual int getQuadIndex(PointID v1, PointID v2, PointID v3, PointID v4);
    /// Returns the index of the tetrahedron given four vertex indices; returns -1 if no tetrahedron exists
    virtual int getTetrahedronIndex(PointID v1, PointID v2, PointID v3, PointID v4);
    /// Returns the index of the hexahedron given eight vertex indices; returns -1 if no hexahedron exists
    virtual int getHexahedronIndex(PointID v1, PointID v2, PointID v3, PointID v4, PointID v5, PointID v6, PointID v7, PointID v8);


    /** returns the index (either 0, 1 ,2 or 3) of the vertex whose global index is vertexIndex. Returns -1 if none */
    virtual int getVertexIndexInTriangle(const Triangle &t, PointID vertexIndex) const;
    /** returns the index (either 0, 1 ,2) of the edge whose global index is edgeIndex. Returns -1 if none */
    virtual int getEdgeIndexInTriangle(const EdgesInTriangle &t, EdgeID edgeIndex) const;

    /** returns the index (either 0, 1 ,2 or 3) of the vertex whose global index is vertexIndex. Returns -1 if none */
    virtual int getVertexIndexInQuad(const Quad &t, PointID vertexIndex) const;
    /** returns the index (either 0, 1 ,2, 3) of the edge whose global index is edgeIndex. Returns -1 if none */
    virtual int getEdgeIndexInQuad(const EdgesInQuad &t, EdgeID edgeIndex) const;

    /** returns the index (either 0, 1 ,2 or 3) of the vertex whose global index is vertexIndex. Returns -1 if none */
    virtual int getVertexIndexInTetrahedron(const Tetra &t, PointID vertexIndex) const;
    /** returns the index (either 0, 1 ,2 ,3, 4, 5) of the edge whose global index is edgeIndex. Returns -1 if none */
    virtual int getEdgeIndexInTetrahedron(const EdgesInTetrahedron &t, EdgeID edgeIndex) const;
    /** returns the index (either 0, 1 ,2 ,3) of the triangle whose global index is triangleIndex. Returns -1 if none */
    virtual int getTriangleIndexInTetrahedron(const TrianglesInTetrahedron &t, TriangleID triangleIndex) const;

    /** returns the index (either 0, 1 ,2, 3, 4, 5, 6, or 7) of the vertex whose global index is vertexIndex. Returns -1 if none */
    virtual int getVertexIndexInHexahedron(const Hexa &t, PointID vertexIndex) const;
    /** returns the index (either 0, 1 ,2 ,3, 4, 5, 6, 7, 8, 9, 10, 11) of the edge whose global index is edgeIndex. Returns -1 if none */
    virtual int getEdgeIndexInHexahedron(const EdgesInHexahedron &t, EdgeID edgeIndex) const;
    /** returns the index (either 0, 1 ,2 ,3, 4, 5) of the quad whose global index is quadIndex. Returns -1 if none */
    virtual int getQuadIndexInHexahedron(const QuadsInHexahedron &t, QuadID quadIndex) const;

    /** \brief Returns for each index (between 0 and 5) the two vertex indices that are adjacent to that edge */
    virtual Edge getLocalEdgesInTetrahedron (const PointID i) const;
    /** \brief Returns for each index (between 0 and 3) the three local vertices indices that are adjacent to that triangle */
    virtual Triangle getLocalTrianglesInTetrahedron (const PointID i) const;

    /** \brief Returns for each index (between 0 and 12) the two vertex indices that are adjacent to that edge */
    virtual Edge getLocalEdgesInHexahedron (const PointID i) const;
    /** \brief Returns for each index (between 0 and 6) the four vertices indices that are adjacent to that quad */
    virtual Quad getLocalQuadsInHexahedron (const PointID i) const;

    /// @name Deprecated names, for backward-compatibility
    /// @{
    const SeqLines& getLines() { return getEdges(); }
    int getNbLines() { return getNbEdges(); }
    Line getLine(LineID i) { return getEdge(i); }
#ifndef SOFA_NEW_HEXA
    const SeqCubes& getCubes() { return getHexahedra(); }
    int getNbCubes() { return getNbHexahedra(); }
    Cube getCube(CubeID i) { return getHexahedron(i); }
#endif
    /// @}

    /// @name Initial points accessors (only available if the topology was loaded from a file containing this information).
    /// Note that this data is only used for initialization and is not maintained afterwards (i.e. topological changes may not be applied)
    /// @{
    virtual bool hasPos() const { return false; }
    virtual double getPX(int) const { return 0.0; }
    virtual double getPY(int) const { return 0.0; }
    virtual double getPZ(int) const { return 0.0; }
    /// @}

    /// Procedural creation methods
    /// @{
    virtual void clear();
    virtual void addPoint(double px, double py, double pz);
    virtual void addEdge( int a, int b );
    void addLine( int a, int b ) { addEdge(a,b); }
    virtual void addTriangle( int a, int b, int c );
    virtual void addQuad( int a, int b, int c, int d );
    virtual void addTetra( int a, int b, int c, int d );
    virtual void addHexa( int a, int b, int c, int d, int e, int f, int g, int h );
    /// @}

    /// get information about connexity of the mesh
    /// @{
    /// Checks if the topology has only one connected component. @return Return true if so.
    virtual bool checkConnexity() {return true;}
    /// Returns the number of connected component.
    virtual unsigned int getNumberOfConnectedComponent() {return 0;}
    /// Returns the set of element indices connected to an input one (i.e. which can be reached by topological links)
    virtual const vector<index_type> getConnectedElement(index_type elem);
    /// @}

    /// get the current revision of this mesh (use to detect changes)
    /// @deprecated
    virtual int getRevision() const { return 0; }

    /// return true if the given cube is active, i.e. it contains or is surrounded by mapped points.
    /// @deprecated
    virtual bool isCubeActive(int /*index*/) { return true; }

    /// Management of topological changes and state changes
    /// @{

    /** \brief Provides an iterator on the first element in the list of TopologyChange objects.
     */
    virtual sofa::helper::list<const TopologyChange *>::const_iterator firstChange() const;

    /** \brief Provides an iterator on the last element in the list of TopologyChange objects.
     */
    virtual sofa::helper::list<const TopologyChange *>::const_iterator lastChange() const;

    /** \brief Provides an iterator on the first element in the list of StateChange objects.
     */
    virtual sofa::helper::list<const TopologyChange *>::const_iterator firstStateChange() const;

    /** \brief Provides an iterator on the last element in the list of StateChange objects.
     */
    virtual sofa::helper::list<const TopologyChange *>::const_iterator lastStateChange() const;

    /// @}


    // functions returning border elements. To be moved in a mapping.
    virtual const sofa::helper::vector <TriangleID>& getTrianglesOnBorder();

    virtual const sofa::helper::vector <EdgeID>& getEdgesOnBorder();

    virtual const sofa::helper::vector <PointID>& getPointsOnBorder();

protected:

    sofa::core::objectmodel::DataFileName fileTopology;
};

} // namespace topology

} // namespace core

} // namespace sofa

#endif
