xcopy /y /a /f /r "../source/shared/RenderComponentData.h" "dx11dllsource/dx11shared"
xcopy /y /a /f /r "../source/shared/RenderComponentData.cpp" "dx11dllsource/dx11shared"
attrib +R  "dx11dllsource/dx11shared/RenderComponentData.h"
attrib +R  "dx11dllsource/dx11shared/RenderComponentData.cpp"