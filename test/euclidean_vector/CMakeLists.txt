cxx_test(
    TARGET euclidean_vector_test1
    FILENAME "euclidean_vector_test1.cpp"
    LINK euclidean_vector
)

cxx_test(
    TARGET euclidean_vector_test_operation
    FILENAME "euclidean_vector_test_operation.cpp"
    LINK euclidean_vector
)
cxx_test(
    TARGET euclidean_vector_test_member
    FILENAME "euclidean_vector_test_member.cpp"
    LINK euclidean_vector
)
cxx_test(
    TARGET euclidean_vector_test_friends
    FILENAME "euclidean_vector_test_friends.cpp"
    LINK euclidean_vector
)
cxx_test(
    TARGET euclidean_vector_test_utility
    FILENAME "euclidean_vector_test_utility.cpp"
    LINK euclidean_vector
)
