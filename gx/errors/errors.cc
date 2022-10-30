//
// weproxy@foxmail.com 2022/10/03
//

#include "errors.h"

namespace gx {
namespace errors {

// New returns an error that formats as the given text.
// Each call to New returns a distinct error value even if the text is identical.
error New(const string& s) { return NewRef<strerr_t>(s); }

// Unwrap returns the result of calling the Unwrap method on err, if err's
// type contains an Unwrap method returning error.
// Otherwise, Unwrap returns nil.
error Unwrap(const error& err) { return err ? err->Unwrap() : nil; }

// Is reports whether any error in err's chain matches target.
//
// The chain consists of err itself followed by the sequence of errors obtained by
// repeatedly calling Unwrap.
//
// An error is considered to match a target if it is equal to that target or if
// it implements a method Is(error) bool such that Is(target) returns true.
//
// An error type might provide an Is method so it can be treated as equivalent
// to an existing error. For example, if MyError defines
//
//	func (m MyError) Is(target error) bool { return target == fs.ErrExist }
//
// then Is(MyError{}, fs.ErrExist) returns true. See syscall.Errno.Is for
// an example in the standard library. An Is method should only shallowly
// compare err and the target and not call Unwrap on either.
bool Is(const error& err_, const error& target) {
    if (!target) {
        return !err_;
    }
    error err = err_;
    for (;;) {
        if (err == target || err->Is(target)) {
            return true;
        }
        err = Unwrap(err);
        if (!err) {
            return false;
        }
    }
}
}  // namespace errors
}  // namespace gx
