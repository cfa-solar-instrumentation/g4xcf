// -----------------------------------------------------------------------------
//  MCTruthManager.cpp
//
//  Class definition of the MC truth manager
//   * Author: Everybody is an author!
//   * Creation date: 15 August 2023
// -----------------------------------------------------------------------------

#include "MCTruthManager.h"

MCTruthManager * MCTruthManager::instance_ = 0;

//-----------------------------------------------------------------------------
MCTruthManager::MCTruthManager()
{}

//-----------------------------------------------------------------------------
MCTruthManager::~MCTruthManager()
{}

//-----------------------------------------------------------------------------
MCTruthManager * MCTruthManager::Instance()
{
    if (instance_ == 0) instance_ = new MCTruthManager();
    return instance_;
}

//-----------------------------------------------------------------------------
void MCTruthManager::EventReset()
{
    // clear containers of generator particles
    initial_generator_particles_.clear();
    final_generator_particles_.clear();

    // delete pointers in MC particle map
    for (auto p : mc_particle_map_)
    {
        delete p.second;
    }

    // clear MC particle map container
    mc_particle_map_.clear();
}

//-----------------------------------------------------------------------------
void MCTruthManager::SetRun(int const value)
{
    run_ = value;
}

//-----------------------------------------------------------------------------
void MCTruthManager::SetEvent(int const value)
{
    event_ = value;
}

//-----------------------------------------------------------------------------
void MCTruthManager::AddInitialGeneratorParticle(GeneratorParticle * particle)
{
    initial_generator_particles_.push_back(particle);
}

//-----------------------------------------------------------------------------
void MCTruthManager::AddFinalGeneratorParticle(GeneratorParticle * particle)
{
    final_generator_particles_.push_back(particle);
}

//-----------------------------------------------------------------------------
void MCTruthManager::AddMCParticle(MCParticle * particle)
{
    mc_particle_map_[particle->TrackID()] = particle;
}

//-----------------------------------------------------------------------------
MCParticle * MCTruthManager::GetMCParticle(int const trackID)
{
    if (mc_particle_map_.count(trackID) < 1)
    {
        std::string message = "\nLine "
                            + std::to_string(__LINE__)
                            + " of file "
                            + __FILE__
                            + "\n\nTrack ID not found: "
                            + std::to_string(trackID)
                            + "\n";
        G4Exception("MCTruthManager::MCTruthManager", "Error",
                    FatalException, message.data());
    }
    return mc_particle_map_.at(trackID);
}

