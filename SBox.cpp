#include "SBox.h"

#define o(y) std::byte(0x ## y)

const std::byte SBox::table[256] =
	{
		o(63), o(7C), o(77), o(7B), o(F2), o(6B), o(6F), o(C5), o(30), o(01), o(67), o(2B), o(FE), o(D7), o(AB), o(76),
		o(CA), o(82), o(C9), o(7D), o(FA), o(59), o(47), o(F0), o(AD), o(D4), o(A2), o(AF), o(9C), o(A4), o(72), o(C0),
		o(B7), o(FD), o(93), o(26), o(36), o(3F), o(F7), o(CC), o(34), o(A5), o(E5), o(F1), o(71), o(D8), o(31), o(15),
		o(04), o(C7), o(23), o(C3), o(18), o(96), o(05), o(9A), o(07), o(12), o(80), o(E2), o(EB), o(27), o(B2), o(75),
		o(09), o(83), o(2C), o(1A), o(1B), o(6E), o(5A), o(A0), o(52), o(3B), o(D6), o(B3), o(29), o(E3), o(2F), o(84),
		o(53), o(D1), o(00), o(ED), o(20), o(FC), o(B1), o(5B), o(6A), o(CB), o(BE), o(39), o(4A), o(4C), o(58), o(CF),
		o(D0), o(EF), o(AA), o(FB), o(43), o(4D), o(33), o(85), o(45), o(F9), o(02), o(7F), o(50), o(3C), o(9F), o(A8),
		o(51), o(A3), o(40), o(8F), o(92), o(9D), o(38), o(F5), o(BC), o(B6), o(DA), o(21), o(10), o(FF), o(F3), o(D2),
		o(CD), o(0C), o(13), o(EC), o(5F), o(97), o(44), o(17), o(C4), o(A7), o(7E), o(3D), o(64), o(5D), o(19), o(73),
		o(60), o(81), o(4F), o(DC), o(22), o(2A), o(90), o(88), o(46), o(EE), o(B8), o(14), o(DE), o(5E), o(0B), o(DB),
		o(E0), o(32), o(3A), o(0A), o(49), o(06), o(24), o(5C), o(C2), o(D3), o(AC), o(62), o(91), o(95), o(E4), o(79),
		o(E7), o(C8), o(37), o(6D), o(8D), o(D5), o(4E), o(A9), o(6C), o(56), o(F4), o(EA), o(65), o(7A), o(AE), o(08),
		o(BA), o(78), o(25), o(2E), o(1C), o(A6), o(B4), o(C6), o(E8), o(DD), o(74), o(1F), o(4B), o(BD), o(8B), o(8A),
		o(70), o(3E), o(B5), o(66), o(48), o(03), o(F6), o(0E), o(61), o(35), o(57), o(B9), o(86), o(C1), o(1D), o(9E),
		o(E1), o(F8), o(98), o(11), o(69), o(D9), o(8E), o(94), o(9B), o(1E), o(87), o(E9), o(CE), o(55), o(28), o(DF),
		o(8C), o(A1), o(89), o(0D), o(BF), o(E6), o(42), o(68), o(41), o(99), o(2D), o(0F), o(B0), o(54), o(BB), o(16)
	};

void SBox::operator()(std::byte & b) const
{
	b = table[std::to_integer<size_t>(b)];
}

const std::byte SBox_Inverse::table[256] =
	{
		o(52), o(09), o(6A), o(D5), o(30), o(36), o(A5), o(38), o(BF), o(40), o(A3), o(9E), o(81), o(F3), o(D7), o(FB),
		o(7C), o(E3), o(39), o(82), o(9B), o(2F), o(FF), o(87), o(34), o(8E), o(43), o(44), o(C4), o(DE), o(E9), o(CB),
		o(54), o(7B), o(94), o(32), o(A6), o(C2), o(23), o(3D), o(EE), o(4C), o(95), o(0B), o(42), o(FA), o(C3), o(4E),
		o(08), o(2E), o(A1), o(66), o(28), o(D9), o(24), o(B2), o(76), o(5B), o(A2), o(49), o(6D), o(8B), o(D1), o(25),
		o(72), o(F8), o(F6), o(64), o(86), o(68), o(98), o(16), o(D4), o(A4), o(5C), o(CC), o(5D), o(65), o(B6), o(92),
		o(6C), o(70), o(48), o(50), o(FD), o(ED), o(B9), o(DA), o(5E), o(15), o(46), o(57), o(A7), o(8D), o(9D), o(84),
		o(90), o(D8), o(AB), o(00), o(8C), o(BC), o(D3), o(0A), o(F7), o(E4), o(58), o(05), o(B8), o(B3), o(45), o(06),
		o(D0), o(2C), o(1E), o(8F), o(CA), o(3F), o(0F), o(02), o(C1), o(AF), o(BD), o(03), o(01), o(13), o(8A), o(6B),
		o(3A), o(91), o(11), o(41), o(4F), o(67), o(DC), o(EA), o(97), o(F2), o(CF), o(CE), o(F0), o(B4), o(E6), o(73),
		o(96), o(AC), o(74), o(22), o(E7), o(AD), o(35), o(85), o(E2), o(F9), o(37), o(E8), o(1C), o(75), o(DF), o(6E),
		o(47), o(F1), o(1A), o(71), o(1D), o(29), o(C5), o(89), o(6F), o(B7), o(62), o(0E), o(AA), o(18), o(BE), o(1B),
		o(FC), o(56), o(3E), o(4B), o(C6), o(D2), o(79), o(20), o(9A), o(DB), o(C0), o(FE), o(78), o(CD), o(5A), o(F4),
		o(1F), o(DD), o(A8), o(33), o(88), o(07), o(C7), o(31), o(B1), o(12), o(10), o(59), o(27), o(80), o(EC), o(5F),
		o(60), o(51), o(7F), o(A9), o(19), o(B5), o(4A), o(0D), o(2D), o(E5), o(7A), o(9F), o(93), o(C9), o(9C), o(EF),
		o(A0), o(E0), o(3B), o(4D), o(AE), o(2A), o(F5), o(B0), o(C8), o(EB), o(BB), o(3C), o(83), o(53), o(99), o(61),
		o(17), o(2B), o(04), o(7E), o(BA), o(77), o(D6), o(26), o(E1), o(69), o(14), o(63), o(55), o(21), o(0C), o(7D)
	};

void SBox_Inverse::operator()(std::byte & b) const
{
	b = table[std::to_integer<size_t>(b)];
}
