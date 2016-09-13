#ifndef LOCAL_PLANNER_BFS_STATIC_H
#define LOCAL_PLANNER_BFS_STATIC_H

/// PROJECT
#include <path_follower/local_planner/local_planner_bfs.h>
#include <path_follower/local_planner/local_planner_static.h>

class LocalPlannerBFSStatic : public LocalPlannerBFS, public LocalPlannerStatic
{
public:
    LocalPlannerBFSStatic(PathFollower& controller, tf::Transformer &transformer,
                       const ros::Duration& update_interval);
private:
    virtual void evaluate(double& current_p, LNode*& succ, double& dis2last,
                          const std::vector<Scorer::Ptr>& scorer,
                          const std::vector<double>& wscorer) override;
};

#endif // LOCAL_PLANNER_BFS_STATIC_H
