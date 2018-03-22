/*todo:
    initial tagger should 
    parse rules from plaintext
    apply rules onto the corpus in order
        -this should be able to test rules for 
        error improvement using enum methods (format: if previous tag is this,
        do this)
        -should be able to apply rules and generate a result corpus

            -test rule
            -apply rule
    
    parallelize init
    typedef enum{
        PREV_TAG_IS=0,
        NEXT_TAG_IS=1,
        PREV_2_TAG_IS=2,
        NEXT_2_TAG_IS=3,
        PREV_1_OR_2_TAG_IS=4, 
        NEXT_1_OR_2_TAG_IS=5,
        PREV_1_OR_2_OR_3_TAG_IS=6,
        NEXT_1_OR_2_OR_3_TAG_IS=7,
        PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y=8,
        PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y=9,
        NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y=10
    }known_word_rules_t;

*/