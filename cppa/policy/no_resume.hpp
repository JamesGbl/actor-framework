#ifndef NO_RESUME_HPP
#define NO_RESUME_HPP

#include <chrono>
#include <utility>

#include "cppa/policy/resume_policy.hpp"

namespace cppa {
namespace util {
struct fiber;
} // namespace util
} // namespace cppa

namespace cppa { namespace policy {

// this policy simply forwards calls to @p await_data to the scheduling
// policy and throws an exception whenever @p resume is called;
// it intentionally works only with the no_scheduling policy
class no_resume {

 public:

    template<class Base, class Derived>
    struct mixin : Base {

        template<typename... Ts>
        mixin(Ts&&... args) : Base(std::forward<Ts>(args)...) { }

        inline resumable::resume_result resume(util::fiber*) {
            this->act();
            return resumable::done;
        }
    };

    template<class Actor>
    void await_ready(Actor* self) {
        self->await_data();
    }

};

} } // namespace cppa::policy

#endif // NO_RESUME_HPP