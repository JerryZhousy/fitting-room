#include "MakeupPlan.h"

#include <cstdio>

static int g_failures = 0;
#define CHECK(expr)                                                     \
    do {                                                                \
        if (!(expr)) {                                                  \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            ++g_failures;                                               \
        }                                                               \
    } while (0)

int main() {
    using OS::MakeupPlan::FaceManagementAllowed;

    // Compile-time evaluation verification (must be constexpr and noexcept)
    static_assert(FaceManagementAllowed(true, true) == true);
    static_assert(FaceManagementAllowed(true, false) == false);
    static_assert(FaceManagementAllowed(false, true) == false);
    static_assert(FaceManagementAllowed(false, false) == false);

    // Case 1: Capable runtime (Overlay v2 available) and user setting enabled -> allowed
    CHECK(FaceManagementAllowed(true, true) == true);

    // Case 2: Legacy runtime without Overlay v2 (e.g. Skyrim SE 1.5.97 / RaceMenu 0.4.16) -> disabled
    // Prevents base tint list corruption and facial whitening/over-illumination bugs
    CHECK(FaceManagementAllowed(true, false) == false);

    // Case 3: User explicitly disabled face appearance management in [Compat] bManageFaceAppearance=0 -> disabled
    CHECK(FaceManagementAllowed(false, true) == false);

    // Case 4: Both disabled -> disabled
    CHECK(FaceManagementAllowed(false, false) == false);

    if (g_failures == 0) {
        std::printf("test_facemanagementgate: all 4 states passed\n");
    }
    return g_failures == 0 ? 0 : 1;
}
