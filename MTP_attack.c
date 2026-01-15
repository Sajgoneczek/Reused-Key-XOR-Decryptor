#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For malloc, free
#include <ctype.h>  // For isprint, isalpha
#include <limits.h> // For LONG_MIN

// Author: Eryk Tokarek
// Last modified: 15.01.2025 (DD.MM.YYYY) 7:30 (hh:mm)

// Ciphertext Array, will add a feature enabling to load ciphers from a file at some point
const char *hex_ciphers[] = {
    "8503C762E70A52F305827C251127A8A29A139272973A1FF7D7BD6FB5D7FA44FD82AA3FC9006ECB4146ADF754DD5168230923FBAECAA088F83C45074AA55A89BCBF14DE6AFA0A00F308D676",
    "B513DA67E70C54FF1ED6393E013CBFB5CE1BDD6FDF3E03E1C6EF79A394EB4EE7C4A83ED5423AC0555EE4EA59DD577E660E71F4AFCDE697F83E5A0049E00A84B3AF5ACD7AE30C41F412C77C6B1D33",
    "B70FDE67E71054F305CB6D32523AA3F287148979D02D18F0DBE12A919EED43FC91B77BCD1B6ECA4544B0EA4E9C47786C137DBAA1D7E686FE254D0A46E058C5BEB90FC66BA2134FFE0FC4606B063DB4",
    "B513DA67E70C54FF1ED6356B0030A1BE8F03DD73DB3B51E9C7BC79A790FC58BFC4AC298C0774C84549B0A3409C5F7860143EEFB399A286FE3000494CEB4EC5A9BE1F8A7DE71D45F310C76B6B053AA4BE8A",
    "BE1BDC6AA2104FBA0BC778250175A5BDCE1E9868D23C05A4D1BA69AED7ED4AFE94A629C5007D8C006FB2E643DD5A77230939FFE0DDA793EB715E0C40E4438BAEF60FC47DE71F44FB04CE7C6B053CA5BA810F89",
    "A212CF2FE91B59B646C3776B1331A7B79C099C6ECE7F12EBD7A36EE684ED42FF88E33AC01A7FD00048ADF75EDD5A7F230923FBAECAAF93A6715C0659E04491B4B716C676A20E52F502D77A221C32",
    "BB1FCB61EB1047FC13CE39281A34BFB58B09DD75D97F05ECC7EF6EA394EB52E390A63F8C037FD1534BA3E60D924131601C24E9A9D7A1C7FA23431D42E64589FDB01BC363F70C45E948",
    "970FDE67E71054F305C36D2E1675B4BC8D08846CC3361EEA82E74B83DEB94AF780B13EDF1D7FD1005EACEA5EDD5A62700834BAA2C0E684E53C4E0043EC4482FDB515C469EB1A45F412CB78271B21A8",
    "B714CE2FEB1054FF01D0703F0B75A1A0810E987FC3361EEA82A664E698F74EB387B122DC1A75C5524BB4EB449E137E731823FBB4D0A989A471651D0DE04496A8A41FD92FF61641EE46C6783F1375B9B39D",
    "B815DE2FE01B45F446C3753F1727B4B6CE1B9378973003EDC5A664A783FC58B382B134C14E7B824C4FA3EA59945E70771871E9A5D7A282F8715B0142A55A8AAEA51FD97CE70D00EE0EC739381736A3B79A",
    "BD1FD321A2374EBA27E73938113DB4BF8B09D13CC42A12EC82AE79E6B6DC78BEA380168C0168826342A5C0459C01212E2D3EF6B988F5D7BF7D0C080DC84F96AEB71DCF2FC30B54F203CC6D221134A5BB8114",
    "9515CE6AA2566DDB258B39240075A5B3895A946F973C1EE9D2BA7EA393B944E581B17BCE016ECA005EACE60D9E5A616B1823EEA5C1B2C7EB3F484942F55E8CB2B81BC62FE30D53F505CB783F1731",
    "B21BDE6EAE5E41F60ACD6E221C32F1A6861FDD6ED23C14EDD4AA78E683F60BE581B132CA173AC3555EACE643895A726A0928BAA2DCA088F8340C0D48E6589CADA213C561AC5E74F20FD1393B0030A7B7800E8E",
    "BB1BC666E1174FEF15827424163CB7BB8D1B8975D83102A4C3A16EE685FC5BFF85BA7BCD1A6EC34341B7AD0DA840786D1A71E9B9D4AB82FE23450A0DE04486AFAF0ADE66ED1000FB0ACD772E",
    "B719C266E70845E946CD77270B75A2B78D08987FCE7351E6D7BB2AA782ED43F68AB732CF0F6EC7440AA1ED4E8F4A6177143EF4E0DEB386F830421D48E059C5A9BE1BDE2FEF1B53E907C57C385234A3B7",
    "B415DE67A21D4FF400CB7D2E1C21B8B3825A9C72D37F05F6D7BC7EB198EB5FFB9DEF7BDB0673C1480AADF00D984062661325F3A1D5E68EE471410649E0588BFDA51FC97AF01B00F909CF743E1C3CB2B39A13927299",
    "9F0E8A62EB1948EE46D17C2E1F75A2A7881C947FDE3A1FF082BB65E687EB44E781A02F8C037FD1534BA3E60D945D65661A23F3B4C0E685F3714D195DE04481B4B81D8A6EA21D52E316D6762C0034A1BA8719",
    "BE1BD967A21146BA12CA7C6B0239B0BB800E9864C37351E6D7BB2AB29FF058B385B32BDE017BC1480AADF00D9B467F671C3CFFAECDA78BE6280C0043F64F86A8A41F842FD1174EF90382712A013DB4A1",
    "BA13C16AA22D68DB4B902C7D5231BEF28015893CD33A01E1CCAB2AA999B94AB397A638DE0B6E824B4FBDAF0D9C5D31620925FBA3D2A395AA324D070DF74F86B2BB0ADF7BE75E54F20382712A013DF1B48108",
    "B714D32FEF1144F300CB7C2F5238B4A19D1B9A79973E1FE082BD6FB69BF848F6C4A134D8063AD6484FE4E74C895231621335BAA9CDB5C7E2305F010DEC44C5A9A41BC47CEB0A0EBA32CA7C6B0030B2B7870C986E",
    "A115DF63E65E54F203CC392A1136B4A29A5A8974D27F05E5CFBF6FB492FD0BFE81B028CD097F824159E4F54C915A75231F34F9A1CCB582AA25440C0DED4B96B5F617CB7BE11645E946D6712E523BB4A5",
    "B515C47BE71054B446F6766B0227B4A48B14893CC33718F78EEF6BE6BAD868B391B03EDF4E7B82534FA7F14889137A660471F3AE99A783EE38580042EB0A91B2F60EC26AA21345E915C37E2E5E75BCB38513937B",
    "BF0E8A66EF0E4FE915CB7B271775B7BD9C5A9C72973E05F0C3AC61A385B95CFA90AB34D91A3AD6484FE4E8488413656C5D37F5B2DEA3C7EB715A0841EC4EC5A9B71D842FD61649E946C777380727B4A1",
    "A212CB7BA21F4EE346C1712A1C32B4F28714DD68DF3A51E7CBBF62A385ED4EEB90E334DE4E7BD15345A7EA4C895675231930EEA199AF94AA35491D48E65E80B9F613C762E71A49FB12C775325C",
    "970FDE67E71054F305C36D2E1675B4BC8D08846CC3361EEA82BB62B384B948FC89A132C20B69825442A1A35F925F74705D3EFCE0DCA884F8285C1D44EA44C5BCB81E8A42C33D00F308D6766B1375A2BB801D91799B",
    "B515C26AF01B4EEE46C67C381B32BFF29A129C68972F03E1D4AA64B284B949FC90AB7BC90F6CC7534EB6EC5D8D5A7F645D30F4A499AB86E4385C1C41E45E8CB2B8568A78EA1743F246C36B2E5230A0A78F169165",
    "BF17DA60F00A41F412826D230030B0A69D5A9472972C14E7D7BD6FE693F04CFA90A2378C0D75CF4D5FAAEA4E9C47786C1371E9B9CAB282E72202"};

// Holds a byte array and its length
typedef struct
{
    unsigned char *data;
    size_t len;
} ByteCipher;


// Converts a single hex char to its int value
int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1; // Error
}

unsigned char *hex_to_bytes(const char *hex_str)
{
    size_t hex_len = strlen(hex_str);
    if (hex_len % 2 != 0)
        return NULL; // Must be even length

    size_t byte_len = hex_len / 2;
    unsigned char *byte_array = malloc(byte_len);
    if (!byte_array)
        return NULL; // Allocation error

    for (size_t i = 0; i < byte_len; i++)
    {
        int high = hex_char_to_int(hex_str[i * 2]);
        int low = hex_char_to_int(hex_str[i * 2 + 1]);
        if (high == -1 || low == -1)
        {
            free(byte_array);
            return NULL; // Invalid hex char
        }
        byte_array[i] = (unsigned char)((high << 4) | low);
    }
    return byte_array;
}

int score_byte(unsigned char b)
{
    // Space and ehmmmmm some type of spacing
    if (b == ' ')
        return 4;
    if (b == '\n' || b == '\r' || b == '\t')
        return 1;

    // Lowercase letters
    if (strchr("etaoin", b)) return 8; // Highest value
    if (strchr("shrdlu", b)) return 6;
    if (strchr("cmfwygpb", b)) return 4;
    if (strchr("vkxqjz", b)) return 2; // Lowest value

    // Uppercase letters
    if (strchr("ETAOIN", b)) return 6; // Highest value
    if (strchr("SHRDLU", b)) return 4;
    if (strchr("CMFWYGPB", b)) return 2;
    if (strchr("VKXQJZ", b)) return 1; // Lowest value

    // Numbers, interpunction signs
    if (strchr("0123456789.,:;?!()-/\\\'\"", b))
        return 2;

    // NOT printable symbols
    if (b >= 32 && b <= 126)
        return 0;

    // Junk
    return -5;
}

// Main function

int main()
{
    size_t NUM_CIPHERS = sizeof(hex_ciphers) / sizeof(hex_ciphers[0]);

    ByteCipher *byte_ciphers = malloc(NUM_CIPHERS * sizeof(ByteCipher));
    if (byte_ciphers == NULL)
    {
        fprintf(stderr, "Alloc error for cipher array\n");
        return 1;
    }

    size_t min_len = (size_t)-1; // Start at max value
    size_t max_len = 0;          // Start at 0

    printf("Analyzing %zu ciphers...\n", NUM_CIPHERS);

    for (size_t i = 0; i < NUM_CIPHERS; i++)
    {
        byte_ciphers[i].data = hex_to_bytes(hex_ciphers[i]);
        if (byte_ciphers[i].data == NULL)
        {
            fprintf(stderr, "HEX structure Error in cipher %zu\n", i);
            // Free already allocated memory before exiting
            for (size_t j = 0; j < i; j++)
                free(byte_ciphers[j].data);
            free(byte_ciphers);
            return 1;
        }
        byte_ciphers[i].len = strlen(hex_ciphers[i]) / 2;

        if (byte_ciphers[i].len < min_len)
        {
            min_len = byte_ciphers[i].len;
        }
        if (byte_ciphers[i].len > max_len)
        {
            max_len = byte_ciphers[i].len;
        }
    }

    printf("Shortest cipher: %zuB. Longest cipher: %zuB.\n", min_len, max_len);
    printf("Attacking key up to length: %zuB\n", max_len);

    unsigned char *recovered_key = malloc(max_len);
    if (!recovered_key)
    {
        fprintf(stderr, "Alloc error for key\n");
        // Free memory
        for (size_t i = 0; i < NUM_CIPHERS; i++)
            free(byte_ciphers[i].data);
        free(byte_ciphers);
        return 1;
    }

    // Main Attack Loop
    for (size_t i = 0; i < max_len; i++) // For each "column" (key byte)
    {
        long best_score = LONG_MIN;
        int best_key_byte = 0;
        int valid_ciphers_count = 0; // How many ciphers are this long?

        for (int key_guess = 0; key_guess <= 255; key_guess++) // Test all 256 possibilities
        {
            long current_score = 0;
            valid_ciphers_count = 0;

            // Check this key guess against all ciphers
            for (size_t c_idx = 0; c_idx < NUM_CIPHERS; c_idx++)
            {
                if (i < byte_ciphers[c_idx].len)
                {
                    unsigned char decrypted_byte = byte_ciphers[c_idx].data[i] ^ key_guess;
                    current_score += score_byte(decrypted_byte);
                    valid_ciphers_count++;
                }
            }

            if (valid_ciphers_count < 2)
            {
                best_score = 0;
                best_key_byte = 0; // Use 0x00 as a placeholder
                break;             // Exit the key_guess loop
            }

            if (current_score > best_score)
            {
                best_score = current_score;
                best_key_byte = key_guess;
            }
        }
        recovered_key[i] = (unsigned char)best_key_byte;

        if (valid_ciphers_count < 2)
        {
            printf("Warning: Key recovery for index %zu is unreliable (pool size: %d)\n", i, valid_ciphers_count);
        }
    }

    // Print Results

    printf("\n--- RECOVERED KEY (HEX) ---\n");
    for (size_t i = 0; i < max_len; i++) // Print full key
    {
        printf("%02x", recovered_key[i]);
    }
    printf("\n");

    printf("\n--- DECODING ---\n");
    for (size_t i = 0; i < NUM_CIPHERS; i++)
    {
        printf("M[%02zu]: ", i);
        for (size_t j = 0; j < byte_ciphers[i].len; j++)
        {
            // This is safe because j < byte_ciphers[i].len <= max_len
            unsigned char decrypted_char = byte_ciphers[i].data[j] ^ recovered_key[j];

            if (isprint(decrypted_char) || decrypted_char == '\n' || decrypted_char == '\t')
            {
                putchar(decrypted_char);
            }
            else
            {
                putchar('?'); // Replace non-printable with a "?"
            }
        }
        printf("\n");
    }

    // Cleanup
    printf("\nFreeing mem...\n");

    // Free each internal cipher's data
    for (size_t i = 0; i < NUM_CIPHERS; i++)
    {
        free(byte_ciphers[i].data);
    }
    // Free the key
    free(recovered_key);

    // Free the array of structures
    free(byte_ciphers);

    return 0;
}