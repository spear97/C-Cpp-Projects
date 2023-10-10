#ifndef SIMULATOR
#define SIMULATOR

#include "Vector.h"
using namespace mathtool;

#include "Agent.h"

#include <vector>
using namespace std;

class Simulator {
   public:

      //Constructor
      Simulator(); 

      //Add Agent(s) into the Simulation
      void AddMember(int index, double x, double y, bool _adv);

      //Render the Simulation
      void Draw();

      //Update the Simulation
      void Update();

      //Send Control to attend to control a given AI Agent
      void SendControl(string control);

      //Toggle an AI Agent by type
      void ToggleControlledAdversary();
      void ToggleControlledAgent();

      //Get the Follow Point that a Possesed AI Agent is at
      Vector3d GetPointToFollow();

   private:
      vector<Agent> agents;
      int controlAgentIndex;
};

#endif
