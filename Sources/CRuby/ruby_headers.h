/* Generated by cfg-cruby 2.1.0 */
#include "ruby/ruby.h"
#include "ruby/ruby/debug.h"
/* We have to knock these next three out because the Ruby regex implementation
   duplicates an identifier (re_pattern_buffer) with /usr/include/regex.h.
   And on Linux, the SwiftGlibC module pulls in every header known
   to man so the clash is unavoidable.  Could make this !__linux__ but
   probably better to keep CRuby API the same.
   Will try and fix for Ruby 2.6
*/
#if 0
#include "ruby/ruby/encoding.h"
#include "ruby/ruby/io.h"
#include "ruby/ruby/re.h"
#endif
#include "ruby/ruby/thread.h"
#include "ruby/ruby/version.h"
#include "ruby/ruby/vm.h"
