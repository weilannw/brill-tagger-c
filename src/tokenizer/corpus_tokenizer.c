/*
    This will read the file into a memory map--structure of 
    how data is layed out in the memory
    map will determine the structure of the data types used for
    optimizing multi threaded code.

    One idea for the memory map is for the corpus preformatter
    to have every line space-padded to the maximum tag length
    so that changes to the tags will not result in a SIGBUS error.
    either that, or the hashing function will be replaced by a simple
    int conversion on the original corpus to create a new corpus
    in which tags are represented as integers. 

    There will need to be two memory maps per thread, 
    one for the training corpus, 
    and one for the corresponding corpus which is stripped of 


    All threads will start with their own portion of training-corpus
        Not a lot of documentation on rule instantiation -- possible method:
            -most frequent tag error will need to be found 
                -eg tag is tag1 but should be tag2
            -iterate through all contextual
                rule templates, instantiating them with this most frequent tag 
                 (eg tag1>tag2), and the most frequent surrounding 
                tags (only consider:
                        -the incorrectly tagged words
                        to which the conversion applies (tag1->tag2)
                        -surrounding tags that are free of 
                        errors
                        -when instantiating rules
                    -1st prev, 2nd prev, 3rd prev
                    -1st next, 2nd next, 3rd next
                -test each rule on the corpus, keeping the rule that reduces the error the most
                and add it to the rule list, applying it to the actual corpus.
                test

                things to store during initial error search:
                -a 2d array of error types storing indices of all errors of a type
                 for quick retrieval
                on calculating most common errors:
                -now store the surrounding tags for each index for 

*/