#include <kamek.h>
#include <game/bases/d_lytbase.hpp>
#include <game/bases/d_message.hpp>

// Provide alternative TPaneNameRegister that uses the custom BMG
void LytBase_c::TPaneNameRegister2(const char **textboxNames, const int *messageIDs, int messageGroup, int count) {
    MsgRes_c *msgRes = dMessage_c::getPropelMsgRes();

    for (int i = 0; i < count; i++) {
        LytTextBox_c *textBox = findTextBox(textboxNames[i]);
        textBox->setMessage(msgRes, messageGroup, messageIDs[i], 0);
    }
}
