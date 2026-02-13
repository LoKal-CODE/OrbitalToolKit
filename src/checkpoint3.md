# Checkpoint 3 - Algorithms and Analysis

    - Write a 1-2 page summary of the algorithms and analysis you need to do on your data. The depth of your analysis can depend on your previous experienc with algorithms and math. Some options for analysis include
        - Searching for specific values and general statistics about the data
        - Optimizing for a given set of constraints
        - Classification of data into different categories through supervised or unsupervised learning
        - Simulation of a system using data as the model
        - Visualization of the data as heat maps, graphs, charts, etc

    -Your writeup should include an explanation of how the algorithms work and justification for why you selected the algorithms that you did for the problem you’re trying to solve

## Application to OrbitalToolKit:

    - Assume for the moment that the toolkit will only have Hohmann Transfer calculations, and can be expanded later.

    - Orbital Velocity: v_orb = sqrt(G*M / r)
        - Inputs: Gravitatonal constant for the specific body (G), mass of the specific body (M), oribtal radius (r)

    - Hohmann Transfer Delta-V Calculation (2 burn):
        - Burn 1 (Departure): delta_v1 = v_orb_1 * ( sqrt(2r_2 / (r_1 + r_2) ) - 1)  ** v_orb_1 is v_orb @ r_1 **
        - Burn 2 (Arrival): delta_v2 = v_orb_2 * (1 - sqrt( 2r_1 / (r_1 + r_2) ) ** v_orb_2 is v_orb @ r_2 ** 
        - Delta-V Total: delta_v_total = | delta_v1 | + | delta_v2 |
        - Inputs: Initial radius r_1, Final radius r_2, ( Central body Gravitatonal constant G, Central body mass M ) v_orb if stored as a varable

    - Transfer Time: Calculate semi-major axis of transfer ellipse, then period
        - a_transfer = (r_1 + r_2) / 2 
        - T_transfer = pi * sqrt( a^3 / G*M )
        - Inputs: Initial radius r_1, Final radius r_2, ( Central body Gravitatonal constant G, Central body mass M ) v_orb if stored as a varable

    - Sources:
        - https://en.wikipedia.org/wiki/Orbital_elements
