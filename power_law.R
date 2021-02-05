ts_table <- read.table("Data/File_2_Size-128_Time-10000_Seed-123456.txt", sep="\t", header=FALSE )

colnames(ts_table) <- c("time", "avalanche_size")

ts_size <- length(ts_table$avalanche_size)

ts_hist <- hist( ts_table$avalanche_size, breaks=ts_size, plot=FALSE )

plot( x=ts_hist$mids, y=ts_hist$density, log="xy", xlab='Avalanche Size', ylab='Frequency' )

ts_df <- data.frame( ts_hist$mids, ts_hist$density  )

write.table( ts_df, "Frequency_Size-128_Time-10000_Seed-123456.txt", sep="\t", row.names=FALSE )
