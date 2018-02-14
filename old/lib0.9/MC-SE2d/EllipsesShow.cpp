#include <iostream>
#include <cmath>

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoGroup.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDrawStyle.h>

const int N = 4;
float dL=4.5, L=N*dL, Lhalf=L/2.0;


double x[N*N],y[N*N],angle[N*N];
SoTransform *position[N*N];



SoSeparator *MySoSimbox(){
  SoSeparator *box =  new SoSeparator; box->ref();
  SoMaterial *mM = new SoMaterial;
  mM->diffuseColor.setValue(1.0, 1.0, 0.0);
  box->addChild(mM);
  SoDrawStyle *ds = new SoDrawStyle;
  ds->lineWidth=4;
  ds->style=SoDrawStyle::LINES;
  box->addChild(ds);
  SoTransform *myXform = new SoTransform; 
  myXform->scaleFactor.setValue(Lhalf, Lhalf, 2);
  box->addChild(myXform); 
  box->addChild(new SoCube); 
  
  box->unrefNoDelete(); return box;
}

SoGroup* AddSoParticles(SoSeparator *root){
 
  for(int ix=0;ix<N;ix++){
  for(int iy=0;iy<N;iy++){
  	SoSeparator *particle;
	int i=ix+N*iy;
	particle = new SoSeparator;
	position[i] = new SoTransform;
	position[i]->scaleFactor.setValue(1.0, 2.0, 1.0);
	angle[i]=0.0*M_PI/180.0;
	position[i]->rotation.setValue(0.0,0.0,1.0,angle[i]);
	x[i]=dL*(ix+0.5)-Lhalf; y[i]=dL*(iy+0.5)-Lhalf;
	position[i]->translation.setValue(x[i],y[i],0);
	particle->addChild(position[i]); 
	particle->addChild(new SoSphere); 
   	root->addChild(particle);
   }}

}

void rwPosition(){
		for(int ix=0;ix<N;ix++) for(int iy=0;iy<N;iy++){
		int i = ix+N*iy;
		x[i]+=0.1*(drand48()-0.5); y[i]+=0.1*(drand48()-0.5);
		position[i]->translation.setValue(x[i],y[i],0);
		angle[i]+= (drand48()-0.5)*M_PI/180.0;
		position[i]->rotation.setValue(0,0,1,angle[i]);
	}
}


main(int , char **argv)
{
//	   SoDB::init();
	
   Widget myWindow = SoXt::init(argv[0]);
   if (myWindow == NULL) exit(1);

   SoSeparator *root = new SoSeparator;
   root->ref();
   
   SoMaterial *myMaterial = new SoMaterial;
   myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);
   root->addChild(myMaterial);

 
// simulation box
  root->addChild(MySoSimbox()); 

//particles (ellipsoid)
  AddSoParticles(root); 
	
	// Render Area
	SoXtRenderArea *myRenderArea = new SoXtRenderArea(myWindow);
    myRenderArea->setSceneGraph(root);
//    myRenderArea->setTitle("2d");
//    myRenderArea->show();

 
   // Set up viewer:
   SoXtExaminerViewer *myViewer = 
            new SoXtExaminerViewer(myWindow);
   myViewer->setSceneGraph(root);
   myViewer->setTitle("Examiner Viewer");
   myViewer->show();
	
   
	SoXt::show(myWindow);
   	SoXt::mainLoop();


}
	

