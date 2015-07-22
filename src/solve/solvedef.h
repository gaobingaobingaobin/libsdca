#ifndef SDCA_SOLVE_SOLVEDEF_H
#define SDCA_SOLVE_SOLVEDEF_H

#include <chrono>
#include <limits>
#include <sstream>

namespace sdca {

enum class solver_status {
  none = 0,
  solving,
  solved,
  no_progress,
  max_num_epoch,
  max_cpu_time,
  max_wall_time
};
typedef typename std::underlying_type<solver_status>::type solver_status_type;
static const char* solver_status_name[] = {
  "none",
  "solving",
  "solved",
  "no_progress",
  "max_num_epoch",
  "max_cpu_time",
  "max_wall_time"
};

using wall_clock = std::chrono::high_resolution_clock;
typedef typename std::chrono::time_point<wall_clock> wall_time_point;
typedef typename std::clock_t cpu_time_point;
typedef typename std::size_t size_type;
typedef typename std::ptrdiff_t difference_type;

template <typename Data>
struct problem_data {
  typedef Data data_type;
  size_type num_dimensions = 0;
  size_type num_examples = 0;
  size_type num_tasks = 0;
  size_type* labels = nullptr;
  data_type* data = nullptr;
  data_type* primal_variables = nullptr;
  data_type* dual_variables = nullptr;

  inline std::string
  to_string() const {
    std::ostringstream str;
    str << "num_dimensions = " << num_dimensions << ", "
           "num_examples = " << num_examples << ", "
           "num_tasks = " << num_tasks;
    return str.str();
  }
};

struct stopping_criteria {
  size_type check_epoch = 1;
  size_type max_num_epoch = 100;
  double max_cpu_time = 0;
  double max_wall_time = 0;
  double epsilon = 1e-3;

  inline std::string
  to_string() const {
    std::ostringstream str;
    str << "epsilon = " << epsilon << ", "
           "check_epoch = " << check_epoch << ", "
           "max_num_epoch = " << max_num_epoch << ", "
           "max_cpu_time = " << max_cpu_time << ", "
           "max_wall_time = " << max_wall_time;
    return str.str();
  }
};

template <typename Result>
struct state {
  typedef Result result_type;
  size_type num_epoch;
  double cpu_time;
  double wall_time;
  result_type primal;
  result_type dual;
  result_type gap;

  state() :
      num_epoch(0),
      cpu_time(0),
      wall_time(0),
      primal(std::numeric_limits<result_type>::infinity()),
      dual(-std::numeric_limits<result_type>::infinity()),
      gap(std::numeric_limits<result_type>::infinity())
    {}

  state(
      const size_type __num_epoch,
      const double __cpu_time,
      const double __wall_time,
      const result_type __primal,
      const result_type __dual,
      const result_type __gap
    ) :
      num_epoch(__num_epoch),
      cpu_time(__cpu_time),
      wall_time(__wall_time),
      primal(__primal),
      dual(__dual),
      gap(__gap)
    {}
};

}

#endif
