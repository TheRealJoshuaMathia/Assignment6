# Assignment6


    auto alg1st = chrono::high_resolution_clock::now();
    auto algsp = chrono::high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(algsp - alg1st);

    d.timer = duration.count();