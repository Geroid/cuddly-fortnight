#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build
  make -f /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build
  make -f /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build
  make -f /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build
  make -f /Users/v.rezvancev/Documents/GitHub/cuddly-fortnight/BattleGame/ios-build/CMakeScripts/ReRunCMake.make
fi

