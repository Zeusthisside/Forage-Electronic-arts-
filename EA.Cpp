ifndef REPUTATION_SYSTEM_H
#define REPUTATION_SYSTEM_H

// Forward declarations (if needed)
class Action;

class Sim {
public:
  // Unique identifier for the Sim
  int sim_id;

  // Sim's name
  std::string name;

  // List of traits associated with the Sim (could be another class)
  std::vector<std::string> traits;

  // Get the current reputation points for a specific category
  virtual int GetReputation(ReputationCategory* category) const = 0;

  // Modify reputation points for a specific category
  virtual void ModifyReputation(ReputationCategory* category, int points) = 0;

protected:
  // Constructor (potentially private)
  Sim(int id, const std::string& name);
};

class ReputationCategory {
public:
  // Name of the reputation category (e.g., Kind, Funny)
  std::string name;

  // Brief description of the category
  std::string description;

  // Maximum achievable reputation points for this category
  int max_points;

private:
  // Constructor (likely private)
  ReputationCategory(const std::string& name, const std::string& description, int max_points);
};

class ReputationManager {
public:
  // Register a new Sim to the reputation system
  void RegisterSim(Sim* sim);

  // Get the reputation data for a specific Sim
  ReputationData* GetReputationData(Sim* sim) const;

  // Process an action performed by a Sim, updating reputation points
  void ProcessAction(Sim* sim, const Action* action);

private:
  // Dictionary to store reputation data for each Sim
  std::unordered_map<int, ReputationData*> sim_data;
};

class ReputationData {
public:
  // Reference to the associated Sim object
  Sim* sim;

  // Dictionary to store reputation points for each category
  std::unordered_map<ReputationCategory*, int> points;

  // Get the current reputation points for a specific category
  int GetPoints(ReputationCategory* category) const;

  // Modify reputation points for a specific category
  void ModifyPoints(ReputationCategory* category, int points);

private:
  // Constructor (likely private)
  ReputationData(Sim* sim);
};

// Abstract class for actions that affect reputation
class Action {
public:
  // Brief description of the action
  std::string description;

  // Get the potential impact of the action on a specific reputation category
  virtual int GetReputationImpact(ReputationCategory* category) const = 0;
};

// ... (Placeholders for specific action classes, e.g., DonateCharityAction, PrankAction)

#endif // REPUTATION_SYSTEM_H