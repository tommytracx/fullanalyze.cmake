/***********************************************************************

This file is part of the FullAnalyze project source files.

FullAnalyze is a software for handling, visualizing and processing lidar 
data (waveforms and point clouds).


Homepage: 

	http://fullanalyze.sourceforge.net
	
Copyright:
	
	Institut Geographique National & CEMAGREF (2009)

Author: 

	Adrien Chauve
	


    FullAnalyze is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FullAnalyze is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public 
    License along with FullAnalyze.  If not, see <http://www.gnu.org/licenses/>.
 
***********************************************************************/

#include <boost/bind.hpp>

#include "layers/VectorLayerGhost.h"


////si GIL
#include "layers/ImageLayer.hpp"
////si ITK
//#include "layers/NewImageLayer.h"

#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/io/tiff_io.hpp>

#include "gui/PanelManager.h"

#include "LidarFormat/geometry/RegionOfInterest2D.h"

#include "PanelViewerFWSensor.h"

PanelViewerFWSensor::PanelViewerFWSensor(wxFrame *parent) :
	PanelViewerFW(parent)
{
}

PanelViewerFWSensor::~PanelViewerFWSensor()
{
}

void PanelViewerFWSensor::addSensorLayer(const shared_ptr<boost::gil::gray32F_image_t>& img)
{
	////si GIL
//	Layer::ptrLayerType layerSensor = ImageLayer::CreateImageLayer(fileName);
	////si ITK
//	Layer::ptrLayerType layerSensor = Layers::NewImageLayer(fileName);

	AddLayer( ImageLayer::CreateImageLayer(*img) );
	Refresh();
}

void PanelViewerFWSensor::setCropCallback(const boost::function<void(const RegionOfInterest2D&)> cropCallback)
{
	m_cropCallback = cropCallback;
}

void PanelViewerFWSensor::setPointCallback(const boost::function<void(const TPoint2D<int>&)> pointCallback)
{
	m_pointCallback = pointCallback;
}

void PanelViewerFWSensor::executeModeGeometryMoving()
{
	//position de la souris
	if (m_geometry == GEOMETRY_POINT)
	{
		m_pointCallback(TPoint2D<int>(m_ghostLayer.m_pointPosition.x, m_ghostLayer.m_pointPosition.y));
	}
//	else if (m_geometry == GEOMETRY_CIRCLE)
//	{
//		//Informe le dock que le point courant a changé
//		Dock *parent = dynamic_cast<Dock*>(m_parent);
//		parent->UpdatePositionVisu2D(TPoint2D<int>(m_ghostLayer.m_circle.first.x, m_ghostLayer.m_circle.first.y));
//	}
//	else if (m_geometry == GEOMETRY_RECTANGLE)
//	{
//		//Informe le dock que le point courant a changé
//		Dock *parent = dynamic_cast<Dock*>(m_parent);
//		parent->UpdatePositionVisuSelection2D(TPoint2D<int>(m_ghostLayer.m_rectangleSelection.first.x, m_ghostLayer.m_rectangleSelection.first.y), TPoint2D<int>(m_ghostLayer.m_rectangleSelection.second.x, m_ghostLayer.m_rectangleSelection.second.y) );
//	}


}





PanelViewerFWSensor* createPanelViewerFWSensor(wxFrame* parent)
{
	return new PanelViewerFWSensor(parent);
}

void PanelViewerFWSensor::Register(wxFrame* parent)
{
	PanelManager::Instance()->Register("PanelViewerFWSensor", boost::bind(createPanelViewerFWSensor, parent));
}




