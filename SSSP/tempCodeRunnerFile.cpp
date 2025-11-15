int sindex, eindex;
        for (int j = 0; j < vertex * (capacity + 1); j++)
        {
            if (adj[j][0].ver == start)
            {
                sindex = j;
                break;
            }
        }
        for (int j = 0; j < vertex * capacity; j++)
        {
            if (adj[j][0].ver == end)
            {
                eindex = j;
                break;
            }