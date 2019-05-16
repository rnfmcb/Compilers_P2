# Compilers_P2-Impliments a Scanner for the compiler 
BNF 

<program>  ->     <vars> <block>
<block>       ->      Begin <vars> <stats> End
<vars>         ->      empty | INT Identifier Integer <vars> 
<expr>        ->      <A> + <expr> | <A> - <expr> | <A>
<A>             ->        <N> * <A> | <N>
<N>             ->       <M> / <N> | <M>
<M>              ->     - <M> |  <R>
<R>              ->      [ <expr> ] | Identifier | Integer
<stats>         ->      <stat> : <mStat>
<mStat>       ->      empty |  <stat>  :  <mStat>
<stat>           ->      <in> | <out> | <block> | <if> | <loop> | <assign>
<in>              ->      Read [ Identifier ]  
<out>            ->      Output [ <expr> ]
<if>               ->      IFF [ <expr> <RO> <expr> ] <stat>
<loop>          ->      Loop [ <expr> <RO> <expr> ] <stat>
<assign>       ->      Identifier  = <expr>  
<RO>            ->      < | = <  | >  | = > | =  =  |   =                            
