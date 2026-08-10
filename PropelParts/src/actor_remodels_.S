.text
.align 4
.set sp, 1

.extern sprintf, strcat, OSReport

.global l_arc_name_buf
.global l_arc_name_format
.global l_arc_name_store

.global getSpriteTexName
getSpriteTexName:
    stwu sp, -0x20(sp)
    mflr r0
    stw r0, 0x24(sp)
    stw r3, 0x1C(sp)
    stw r5, 0x18(sp)
    stw r6, 0x14(sp)
    stw r7, 0x10(sp)
    stw r8, 0xC(sp)
    stw r9, 0x8(sp)

    // Save the arc name for later
    lis r7, l_arc_name_store@h
    ori r7, r7, l_arc_name_store@l
    stw r4, 0x0(r7)

    lis r3, l_arc_name_buf@h
    ori r3, r3, l_arc_name_buf@l

    lis r4, l_arc_name_format@h
    ori r4, r4, l_arc_name_format@l

    or r5, r6, r6

    crclr 4*cr1+eq
    bl sprintf

    // Add the SpriteTex name to the end of the original name
    lis r4, l_arc_name_buf@h // Move "_tXX" to the source field
    ori r4, r4, l_arc_name_buf@l

    // Get the arc name back
    lis r3, l_arc_name_store@h
    ori r3, r3, l_arc_name_store@l

    bl strcat

    // Move the final string to r4 so we
    // can use it for dRes_c::getRes()
    //or r4, r3, r3

    //lis r3, test_msg@h
    //ori r3, r3, test_msg@l

    crclr 4*cr1+eq
    bl OSReport

    lwz r0, 0x24(sp)
    lwz r3, 0x1C(sp)
    lwz r5, 0x18(sp)
    lwz r6, 0x14(sp)
    lwz r7, 0x10(sp)
    lwz r8, 0xC(sp)
    lwz r9, 0x8(sp)
    mtlr r0
    addi sp, sp, 0x20
    blr

.data
l_arc_name_buf:
	.long 0,0,0,0

l_arc_name_format:
	.string "_t%02d"

l_arc_name_store:
    .long 0,0,0,0

test_msg:
    .string "%s\n"
