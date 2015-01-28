#ifndef ERTOOL_PARTICLE_CXX
#define ERTOOL_PARTICLE_CXX

#include "Particle.h"

namespace ertool {

  Particle::Particle(int pdg_code, double mass)
    : _pdg_code(pdg_code)
    , _mass(mass)
    , _vtx(3)
    , _mom(3)
  { 
    if(mass<0)    throw ERException("Must specify mass!");
    if(!pdg_code) throw ERException("Invalid PdgCode!");
    _pdg_code = pdg_code;
    _mass     = mass;

    Reset();
  }

  void Particle::Reset() {

    for(size_t i=0; i<3; ++i) {
      _vtx[i] = kINVALID_DOUBLE;
      _mom[i] = kINVALID_DOUBLE;
    }
    _score = kINVALID_DOUBLE;
    _daughters.clear();
    _reco_obj_id = -1;
    _reco_obj_type = kUnknown;
  }

  //
  // Getters
  //
  double Particle::Energy() const 
  { return sqrt(_mom.SqLength() + _mass * _mass ); }
  double Particle::DaughterEnergySum() const
  { 
    double energy=0;
    for(auto const& d : _daughters) energy += d.Energy();
    return energy;
  }

  //
  // Setters
  //
  void Particle::Vertex(const ::geoalgo::Point_t& vtx)  
  { _vtx.compat(vtx); _vtx = vtx; }
  void Particle::Vertex(const double& x,
			const double& y,
			const double& z)
  { _vtx[0]=x; _vtx[1]=y; _vtx[2]=z; }
  void Particle::Momentum(const ::geoalgo::Vector_t& mom) 
  { _mom.compat(mom); _mom = mom; } 
  void Particle::Momentum(const double& px,
			  const double& py,
			  const double& pz)
  { _mom[0]=px; _mom[1]=py; _mom[2]=pz; }
  void Particle::AddDaughter(const Particle& s) 
  { _daughters.push_back(s); }
  void Particle::RecoObjInfo(const int id, const RecoObjType_t type)
  { _reco_obj_id = id; _reco_obj_type = type; }


  bool Particle::Match(const Particle& p, bool exclusive) const
  {
    if(exclusive) return (Match(p,false) && p.Match(*this,false));

    if(p._pdg_code && _pdg_code && _pdg_code != p._pdg_code) return false;

    std::vector<bool> used_v(_daughters.size(),false);
    for(auto const& p_daughter : p.Daughters()) {

      bool found=false;
      for(size_t i=0; i<_daughters.size(); ++i) {

	if(used_v[i]) continue;

	auto const& my_daughter = _daughters[i];

	if(my_daughter.Match(p_daughter)) {
	  found = true;
	  used_v[i] = true;
	  break;
	}
	
      }
      if(!found) return false;
    }
    return true;
  }

  std::string Particle::Diagram() const
  {
    std::string res;
    Diagram(res);
    return res;
  }

  void Particle::Diagram(std::string& res,std::string prefix) const
  {
    res += prefix + std::to_string(_pdg_code) + "\n";
    prefix += "  ";
    for(auto const& d : _daughters) d.Diagram(res,prefix);
  }

  const std::vector<const ::ertool::Particle*> Particle::AllDaughters() const
  {
    std::vector<const ::ertool::Particle*> res;
    this->AllDaughters(res);
    return res;
  }
  void Particle::AllDaughters(std::vector<const ::ertool::Particle*>& part_v) const
  {
    part_v.push_back(this);
    for(auto const& daughter : _daughters) daughter.AllDaughters(part_v);
  }

}

#endif