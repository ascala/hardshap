#include <Inventor/Sb.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>


#include <SimBox2d.h>
#include <LLcells2d.h>
#include <MCstep2d.h>

#include <ctime>
#include <iostream>
using namespace std;

// Function prototypes
void myKeyPressCB(void *, SoEventCallback *);
void AddParticles(SoSeparator *root);

// Global data
const int NpartMax = 10000;
SbViewportRegion viewportRegion;
SoTransform *coord[NpartMax];
SimBox2d box;

int main(int argc, char **argv) {

/* start Open Inventor stuff */


   // Initialize Inventor and Xt
   Widget myWindow = SoXt::init(argv[0]);
   if (myWindow == NULL) exit(1);

   // Create and set up the selection node
   SoSelection *selectionRoot = new SoSelection;
   selectionRoot->ref();
   selectionRoot->policy = SoSelection::SHIFT;
   
   SoMaterial *myMaterial = new SoMaterial;
   myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);
   selectionRoot->addChild(myMaterial);
	
   // Add a camera and some light
   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   selectionRoot->addChild(myCamera);
   selectionRoot->addChild(new SoDirectionalLight);



   // An event callback node so we can receive key press events
   SoEventCallback *myEventCB = new SoEventCallback;
   myEventCB->addEventCallback(
            SoKeyboardEvent::getClassTypeId(), 
            myKeyPressCB, selectionRoot);
   selectionRoot->addChild(myEventCB);

/*  end  Open Inventor stuff */


#ifdef _RSEED
    srand48(_RSEED);
#else
    srand48(time(NULL));
#endif


    IVec2d Ncell(12,6);
//    IVec2d Ncell(6,6);
                
    box.init(argc,argv);
    if(box.Npart>NpartMax) {cerr << "Too many particles!!!\n"<<flush; exit(1);}

	double rmax=0.5; Vec2d r(0), a(rmax/2,rmax), e(2,2);
//    Circle particle(r,rmax);
    Ellipse particle(r,a);
//    SEllipse particle(r,a,e);
 
	// phimax for sigma=1 sphereres is ~ 0.785397
//    if (!box.create_SQ(0.225,particle,Ncell)) exit(0);//SEllipses
    if (!box.create_SQ(0.15,particle,Ncell)) exit(0);//Ellipses
    
    double side=box.L.x; if(box.L.y>side) side=box.L.y;
	double rcut=2*particle.rmax;
	
	if(side/2<=rcut)
		{cerr<<"rcut "<< rcut<<"to big for L "<<box.L<<flush<<endl;exit(0);}

box.Nstep*=100;

   // Print out usage message
   printf("Press <Up arrow>  for a MC step\n");

/* start Open Inventor stuff */
	AddParticles(selectionRoot);
	
	   // Create a render area for viewing the scene
   SoXtRenderArea *myRenderArea = new SoXtRenderArea(myWindow);
   myRenderArea->setSceneGraph(selectionRoot);
   myRenderArea->setGLRenderAction(new SoBoxHighlightRenderAction());
   myRenderArea->redrawOnSelectionChange(selectionRoot);
   myRenderArea->setTitle("Adding Event Callbacks");

   // Make the camera see the whole scene
   viewportRegion = myRenderArea->getViewportRegion();
   myCamera->viewAll(selectionRoot, viewportRegion, 2.0);


	
	
   // Show our application window, and loop forever...
   myRenderArea->show();
   SoXt::show(myWindow);
   SoXt::mainLoop();
/*  end  Open Inventor stuff */

    return 0;
}



void
myKeyPressCB(void *userData, SoEventCallback *eventCB)
{
   SoSelection *selection = (SoSelection *) userData;
   const SoEvent *event = eventCB->getEvent();

   // check for the Up and Down arrow keys being pressed
   if (SO_KEY_PRESS_EVENT(event, UP_ARROW)) {

	for (int istep = 1; istep <= box.Icounter; ++istep) {

    	NVT_MCstep(box);
        if((istep%box.Icounter)==0) { box.adjust_acceptance();
cerr << "Step: "<< istep << " , Displacement: "<< box.MaxDisp << " , Acceptance: "<< box.ratio << endl;
		}
    }
	for(int i=0;i<box.Npart;i++){
		coord[i]->translation.setValue(box.particles[i].r.x,box.particles[i].r.y,0);
		double angle=atan2(box.particles[i].u[0].y,box.particles[i].u[0].x);
		coord[i]->rotation.setValue(0,0,1,-angle);
	}
      eventCB->setHandled();
   } 
}


void AddParticles(SoSeparator *root){
  for(int i=0;i<box.Npart;i++){
  	SoSeparator *particle = new SoSeparator;
  	{
		coord[i] = new SoTransform;
		Vec2d a = box.particles[i].a;
		coord[i]->scaleFactor.setValue(a.x, a.y, a.x/10);
		double angle=0;
		coord[i]->rotation.setValue(0.0,0.0,1.0,angle);
		Vec2d r = box.particles[i].r;
		coord[i]->translation.setValue(r.x,r.y,0);
  	}
	particle->addChild(coord[i]); 
	particle->addChild(new SoSphere); 
   	root->addChild(particle);
   }


}
